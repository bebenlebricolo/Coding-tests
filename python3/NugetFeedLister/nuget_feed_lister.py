import sys
import requests
from requests.auth import HTTPBasicAuth
import json


# To be used like this :
# python ./nuget_feed_lister.py <service index base url> <username> <user password>
# E.g. :
#   python ./nuget_feed_lister.py https://<devops>/<organisation>/<project>/_packaging/<feed name>/nuget/v3/index.json toto malzdgmladnvmazjbdgmoazjkghdmgakzdbmoazkdgh

def main(args) :
    url=args[0]
    username=args[1]
    pat=args[2]

    headersList = {
        "Accept": "*/*",
        "User-Agent": "Thunder Client (https://www.thunderclient.io)"
    }
    basic_auth=HTTPBasicAuth(username=username, password=pat)

    # Fetch root API of targeted feed name
    response = requests.get(url=url, auth=basic_auth, headers=headersList)
    if response.status_code >= 400 :
        print("Caught error from remote server : returned code was {}".format(response.status_code))
        print(response.json())

    content = json.loads(response.content)

    search_query_service_url=""
    for resource in content["resources"] :
        if "SearchQueryService" in resource["@type"] :
            search_query_service_url=resource["@id"]
            break
    search_request = search_query_service_url + "?q=&take=256"
    search_response = requests.get(url=search_request, headers=headersList, auth=basic_auth)
    if search_response.status_code >= 400 :
        print("Caught error from remote server : returned code was {}".format(response.status_code))
        print(search_response.json())

    packagesList = json.loads(search_response.content)["data"]

    count = len(packagesList)
    print("Listing the {} packages :".format(count))
    for package in packagesList :
        print("Name : {}, Latest Version : {}, Description : {}{}".format(package["id"], package["version"], package["description"][:30], "[...]" if len(package["description"]) >= 30 else "" ))


    return 0



if __name__ == "__main__" :
    exit(main(sys.argv[1:]))