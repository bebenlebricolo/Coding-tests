import sys
import requests
from requests.auth import HTTPBasicAuth
import json
from pathlib import Path
import tempfile


# To be used like this :
# python ./nuget_feed_lister.py <service index base url> <username> <user password>
# E.g. :
#   python ./nuget_feed_lister.py https://<devops>/<organisation>/<project>/_packaging/<feed name>/nuget/v3/index.json toto malzdgmladnvmazjbdgmoazjkghdmgakzdbmoazkdgh

class UnauthorizedException(Exception) :
    def __init__(self, *args: object) -> None:
        super().__init__(*args)

class MissingEndpoint(Exception) :
    def __init__(self, *args: object) -> None:
        super().__init__(*args)

class BaseService :
    url = ""
    name = ""
    version = ""
    auth = HTTPBasicAuth
    def __init__(self, url, name, version, auth : HTTPBasicAuth) -> None:
        self.url = url
        self.name = name
        self.version = version
        self.auth = auth

    def check_status_codes(self, response : requests.Response) -> None :
        if response.status_code < 400 :
            return

        if response.status_code != 401 :
            print("Caught an Unauthorized error code 401, please check your credentials")
            print(response.reason)
            raise UnauthorizedException()

        if response.status_code != 404 :
            print("Input URL is malformed, resource not found. Error message is : {}".format(response.reason))
            print(response.reason)
            raise MissingEndpoint()



class PackagePublishService(BaseService):
    def __init__(self, url, name, version, auth : HTTPBasicAuth) -> None:
        super().__init__(url, name, version, auth)

    def push(self, filepath : Path, apikey = "default", timeout = 0) -> bool :
        content = bytes()
        if not filepath.exists() or not filepath.is_file() :
            print("Could not load file {} for pushing : file is not reachable or does not exist")
            return False

        # Read all file's content
        with open(filepath, "rb") as file :
            content = file.read()

        headers = {
            "Accept": "*/*",
            "User-Agent": "Thunder Client (https://www.thunderclient.io)",
            "X-NuGet-ApiKey" : apikey,
            "Content-Type" : "multipart/form-data"
        }

        response = requests.put(url=self.url, data=content, headers=headers, auth=self.auth)
        try :
            self.check_status_codes(response)
        except Exception as e :
            print(e)
            return False

        if response.status_code == 400 :
            print("Supplied package is invalid")
            return False
        elif response.status_code == 409 :
            print("Supplied package already exists in feed")
            return False

        return True

    def delete(self, packagename, version, apikey = "default", timeout : int = 0) -> bool :
        url = "{}/{}/{}".format(self.url, packagename, version)

        headers = {
            "Accept": "*/*",
            "User-Agent": "Thunder Client (https://www.thunderclient.io)",
            "X-NuGet-ApiKey" : apikey
        }

        response = requests.delete(url=url, headers=headers, auth=self.auth)
        try :
            self.check_status_codes(response)
        except Exception as e :
            print(e)
            return False

        print("Package {} version {} successfully deleted ".format(packagename, version))

        return True

class SearchQueryService(BaseService):
    def __init__(self, url, name, version, auth : HTTPBasicAuth) -> None:
        super().__init__(url, name, version, auth)

    def find_package(self, packagename) -> bool :
        url = "{}?q={}".format(self.url, packagename)

        headers = {
            "Accept": "*/*",
            "User-Agent": "Thunder Client (https://www.thunderclient.io)"
        }

        response = requests.get(url=url, headers=headers, auth=self.auth)
        try :
            self.check_status_codes(response)
        except Exception as e :
            print(e)
            return False

        content = json.loads(response.content)
        print("Found {} packages matching the packagename".format(content["totalHits"]))

        # Dumping contents
        print(content)

        return True

    def list_all_packages(self, limit = 2000) -> bool :
        url = "{}?q=&take={}".format(self.url, limit)

        headers = {
            "Accept": "*/*",
            "User-Agent": "Thunder Client (https://www.thunderclient.io)"
        }

        response = requests.get(url=url, headers=headers, auth=self.auth)
        try :
            self.check_status_codes(response)
        except Exception as e :
            print(e)
            return False

        content = json.loads(response.content)
        print("Found {} packages matching the packagename".format(content["totalHits"]))

        packagesList = content["data"]
        count = len(packagesList)
        print("Listing the {} packages :".format(count))
        for package in packagesList :
            print("Name : {}, Latest Version : {}, Description : {}{}".format(package["id"], package["version"], package["description"][:30], "[...]" if len(package["description"]) >= 30 else "" ))

        return True

class PackageContentService(BaseService):
    def __init__(self, url, name, version, auth : HTTPBasicAuth) -> None:
        super().__init__(url, name, version, auth)

    def enumerate_versions(self, packagename : str, timeout = 0) -> bool :
        url = "{}/{}/index.json".format(self.url, packagename.lower())
        headers = {
            "Accept": "*/*",
            "User-Agent": "Thunder Client (https://www.thunderclient.io)"
        }

        response = requests.get(url=url, headers=headers, auth=self.auth)
        try :
            self.check_status_codes(response)
        except Exception as e :
            print(e)

        content =  json.loads(response.content)
        print("Listing {} package available versions : ".format(packagename))
        for version in content["versions"] :
            print(version)

        return True



    def download(self, packagename : str, version : str, destination_dir : Path, timeout = 0) -> bool :
        lower_id = packagename.lower()
        version_id = version.lower()
        url = "{}/{}/{}/{}.{}.nupkg".format(self.url, lower_id, version_id, lower_id, version_id)

        headers = {
            "Accept": "*/*",
            "User-Agent": "Thunder Client (https://www.thunderclient.io)"
        }

        response = requests.get(url=url, headers=headers, auth=self.auth)
        try :
            self.check_status_codes(response)
        except Exception as e :
            print(e)
            return False

        package_content = response.content
        filename = packagename + "." + version + ".nupkg"
        output_filepath = destination_dir.joinpath(filename)
        try :
            with open(output_filepath, "wb") as file :
                file.write(package_content)
        except IOError as e :
            print("Could not write package to disk because : ")
            print(e)
            return False

        print("Successfully downloaded package {} to {}".format(filename, destination_dir))

        return True


class NugetFeedServices(BaseService):
    package_publish : PackagePublishService
    package_base_address : PackageContentService
    search_query_service : SearchQueryService

    def __init__(self, url, name, version, auth: HTTPBasicAuth) -> None:
        super().__init__(url, name, version, auth)
        self.package_publish = PackagePublishService(url, "PackagePublish", "2.0.0", auth)
        self.package_base_address = PackageContentService(url, "PackageBaseAdress", "3.0.0", auth)
        self.search_query_service = SearchQueryService(url, "SearchQueryService", "3.0.0-beta", auth)


        self.package_base_address.auth = self.auth
        self.package_publish.auth = self.auth
        self.search_query_service.auth = self.auth

    def parse_service_index(self) -> bool :
        headersList = {
        "Accept": "*/*",
        "User-Agent": "Thunder Client (https://www.thunderclient.io)"
        }

        response = requests.get(url=self.url, headers=headersList, auth=self.auth)
        self.check_status_codes(response)

        content = json.loads(response.content)
        for resource in content["resources"] :
            if "SearchQueryService" in resource["@type"] :
                self.search_query_service.url = resource["@id"]
                continue

            if "PackageBaseAddress" in resource["@type"] :
                self.package_base_address.url = resource["@id"]
                continue

            if "PackagePublish" in resource["@type"] :
                self.package_publish.url = resource["@id"]
                continue

        return True



def main(args) :
    url=args[0]
    username=args[1]
    pat=args[2]
    package_name=args[3]
    version=args[4]

    basic_auth=HTTPBasicAuth(username=username, password=pat)

    feed_service = NugetFeedServices(url=url, name="FeedIndexService", version="1.0.0", auth=basic_auth)
    success = feed_service.parse_service_index()

    if not success :
        return 1

    success = feed_service.package_base_address.enumerate_versions(package_name, 0)
    if not success :
        return 1

    success = feed_service.package_base_address.download(package_name, version, Path(tempfile.gettempdir()))

    return 0



if __name__ == "__main__" :
    exit(main(sys.argv[1:]))