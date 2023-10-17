import json
import os
import jwt
import argparse
import sys

from dataclasses import dataclass
from pathlib import Path
import webbrowser
from google.oauth2 import service_account
from google.auth.transport.requests import Request
from google_auth_oauthlib.flow import Flow, InstalledAppFlow

import wsgiref.simple_server
import wsgiref.util
import urllib.parse

import base64
import hashlib
import requests

from ClientSecretsFile import ClientSecretFile


SERVICE_ACCOUNT_FILE_ENV_VAR = "CARLISTAPP_SERVICE_ACCOUNT_FILE"
SERVICE_ACCOUNT_DEFAULT_FILENAME = "service.json"
SCOPES = [
    'https://www.googleapis.com/auth/cloud-platform',
    'https://www.googleapis.com/auth/userinfo.email',
    'https://www.googleapis.com/auth/userinfo.profile',
    "openid"
]


TEST_SERVICE_CONFIG_FILENAME = "test_service.json"

def get_script_dir() -> Path :
    this_dir = Path(__file__).parent
    return this_dir

def generate_code_challenge(code_verifier : str) -> str :
    ascii_version = code_verifier.encode("utf-8")
    hashed_version = hashlib.sha256(ascii_version).digest()
    string_version = base64.urlsafe_b64encode(hashed_version).decode("utf-8").rstrip("=")
    return string_version

def generate_header(token : str) -> dict[str, str]:
    headers = {
        "Authorization" : "Bearer {}".format(token),
        "Accept" : "*/*"
    }
    return headers

def check_service_account_ok(target_audience) -> bool:
    print("Authenticating using service account")
    this_dir = get_script_dir()
    service_account_file =  this_dir.joinpath("Config/" + SERVICE_ACCOUNT_DEFAULT_FILENAME)
    if SERVICE_ACCOUNT_FILE_ENV_VAR in os.environ :
        service_account_file = Path(os.environ[SERVICE_ACCOUNT_FILE_ENV_VAR])

    if not service_account_file.exists() :
        print("Service account file {} does not exist.".format(service_account_file))
        return False

    credentials = service_account.IDTokenCredentials.from_service_account_file(service_account_file, target_audience=target_audience)
    request = Request()
    credentials.refresh(request)
    token = credentials.token

    decoded_token = jwt.decode(token,  options={"verify_signature": False})
    print("Successfully retrieved token for service account {}\n\n".format(decoded_token["email"]))
    print("Token : \n\n" + token)
    return True

def check_client_can_request_token(target_audience) -> bool :
    print("Authenticating using InstalledAppFlow auto OAuth handling")
    this_dir = get_script_dir()
    client_secrets_file = this_dir.joinpath("Config/client_secrets.json")

    if not client_secrets_file.exists() :
        print("Client secrets file does not exist")
        return False

    flow = InstalledAppFlow.from_client_secrets_file(client_secrets_file,
                                                     scopes=SCOPES)
    creds = flow.run_local_server(host="localhost", port=4200)

    #print("Proprietary google OAUTH2 token : {}".format(flow.credentials.token))
    creds = flow.credentials
    creds.audience = target_audience
    #print("token = {}".format(creds.id_token))

    headers = generate_header(creds.id_token)
    response = requests.get(target_audience, headers=headers)
    if response.status_code != 200 :
        print("Failed to authenticate service account")
        return False

    decoded_token = jwt.decode(creds.id_token, options={"verify_signature": False})
    print("Successfully retrieved token for user {}\n\n".format(decoded_token["name"]))
    return True


@dataclass
class TokenFetchResponse:
    access_token : str = ""
    expires_in : int = 3600
    scope : str = ""
    token_type : str = ""
    id_token : str = ""

    def from_json(self, content) :
        self.access_token = content["access_token"]
        self.expires_in = content["expires_in"]
        self.scope = content["scope"]
        self.token_type = content["token_type"]
        self.id_token =  content["id_token"]



def manual_token_generation(target_audience) -> bool :
    print("Trying manual OAuth2.0 authentication procedure")

    this_dir = get_script_dir()
    client_secrets_filepath = this_dir.joinpath("Config/client_secrets.json")

    if not client_secrets_filepath.exists() :
        print("Client secrets file does not exist")
        return False

    client_secret_file = ClientSecretFile()
    parse_result = client_secret_file.from_file(client_secrets_filepath)
    if not parse_result :
        return False

    client_id = client_secret_file.client_id
    client_secret = client_secret_file.client_secret
    redirect_uri = client_secret_file.redirect_uris[1]
    response_type = "code"
    scope = ""
    for item in SCOPES :
        scope += item + ' '
    scope.rstrip(' ')

    code_verifier = "Test code challenge 123456"
    code_challenge = generate_code_challenge(code_verifier)
    code_challenge_method = "S256"
    state = "offline" # Set the value to offline if your application needs to refresh access tokens when the user is not present at the browser.
    #state = "online" # default value

    google_api_oauth_server = client_secret_file.auth_uri
    auth_url = google_api_oauth_server + "?scope={}&response_type={}&state={}&redirect_uri={}&client_id={}".format(scope, response_type, state, redirect_uri, client_id)
    auth_url += "&code_challenge={}&code_challenge_method={}".format(code_challenge, code_challenge_method)

    wsgi_app = _RedirectWSGIApp("Authentication succeeded, you can now close this tab.")
    # Fail fast if the address is occupied
    wsgiref.simple_server.WSGIServer.allow_reuse_address = False
    local_server = wsgiref.simple_server.make_server(
        "localhost", 4200, wsgi_app, handler_class=wsgiref.simple_server.WSGIRequestHandler
    )

    webbrowser.open(auth_url, new=1, autoraise=True)

    local_server.timeout = 360
    local_server.handle_request()
    # Note: using https here because oauthlib is very picky that
    # OAuth 2.0 should only occur over https.
    authorization_response = wsgi_app.last_request_uri
    parsed_auth_response = urllib.parse.unquote(authorization_response)
    auth_code = parsed_auth_response.split("code=")[1].split("&scope=")[0]
    #print("authorization response = " + authorization_response)
    #print("auth_code = " + auth_code)

    local_server.server_close()

    token_url = client_secret_file.token_uri
    token_url += "?code=" + auth_code
    token_url += "&code_verifier=" + code_verifier
    token_url += "&client_id=" + client_id
    token_url += "&client_secret=" + client_secret
    token_url += "&redirect_uri=" + redirect_uri
    token_url += "&grant_type=authorization_code"
    response = requests.post(token_url)

    #print(response.text)
    token_response = TokenFetchResponse()
    token_response.from_json(response.json())

    decoded_token = jwt.decode(token_response.id_token, options={"verify_signature": False} )
    print("Successfully retrieved token for user {}\n\n".format(decoded_token["name"]))
    print(token_response.id_token)

    print("Trying to ping remote cloud run service")
    headers = generate_header(token_response.id_token)
    response = requests.get(target_audience, headers=headers)
    if response.status_code != 200 :
        print("Failed to authenticate service account\n\n")
        return False
    html_returned_page = response.text
    html_page_file = this_dir.joinpath("hello.html")
    with open(html_page_file, 'w') as file :
        file.write(html_returned_page)

    return True




class _RedirectWSGIApp(object):
    """WSGI app to handle the authorization redirect.

    Stores the request URI and displays the given success message.
    """

    def __init__(self, success_message):
        """
        Args:
            success_message (str): The message to display in the web browser
                the authorization flow is complete.
        """
        self.last_request_uri = None
        self._success_message = success_message

    def __call__(self, environ, start_response):
        """WSGI Callable.

        Args:
            environ (Mapping[str, Any]): The WSGI environment.
            start_response (Callable[str, list]): The WSGI start_response
                callable.

        Returns:
            Iterable[bytes]: The response body.
        """
        start_response("200 OK", [("Content-type", "text/plain; charset=utf-8")])
        self.last_request_uri = wsgiref.util.request_uri(environ)
        return [self._success_message.encode("utf-8")]





def main():

    parser = argparse.ArgumentParser()
    parser.add_argument("kind", default="All", choices=["None", "Service", "Manual", "Auto"])
    arguments = parser.parse_args(sys.argv[1:])

    # Find the kind mode
    kind = arguments.kind
    print(f"Token generation mode is set to : {kind}")

    this_dir = Path(__file__).parent

    # Will be replaced by actual Cloud Run service endpoint from config file
    target_audience = "default"

    test_service_filepath = this_dir.joinpath("Config/" + TEST_SERVICE_CONFIG_FILENAME)
    with open(test_service_filepath, "r") as file :
        content = json.load(file)
        target_audience = content["name"]


    match kind :
        case "All" :
            success = manual_token_generation(target_audience)
            success &= check_client_can_request_token(target_audience)
            success &= check_service_account_ok(target_audience)

        case "Service" :
            success = check_service_account_ok(target_audience)

        case "Manual" :
            success = manual_token_generation(target_audience)

        case "Auto":
            success = check_client_can_request_token(target_audience)

        case _:
            print("Wrong mode selected")


if __name__ == "__main__" :
    exit(main())