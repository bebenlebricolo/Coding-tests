import json
from pathlib import Path
from dataclasses import dataclass, field


@dataclass
class ClientSecretFile :
    client_id : str = ""
    client_secret : str = ""
    project_id : str = ""
    auth_uri : str = ""
    token_uri : str = ""
    auth_provider_x509_cert_url : str = ""
    redirect_uris : list[str] = field(default_factory=list)

    def _read_prop(self, prop : str, content : dict) -> str :
        return content[prop]

    def from_json(self, content : dict) :
        webnode = content["web"]
        self.client_id = webnode["client_id"]
        self.client_secret = webnode["client_secret"]
        self.project_id = webnode["project_id"]
        self.auth_uri = webnode["auth_uri"]
        self.token_uri = webnode["token_uri"]
        self.auth_provider_x509_cert_url = webnode["auth_provider_x509_cert_url"]
        self.redirect_uris = []
        for elem in webnode["redirect_uris"] :
            self.redirect_uris.append(elem)

    def from_file(self, filepath : Path) -> bool :
        if not filepath.exists() :
            print("File does not exist. Can not parse file.")
            return False

        with open(filepath, "r") as file :
            content = json.load(file)
            self.from_json(content)

        return True

