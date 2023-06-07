import firebase_admin
from firebase_admin import auth
from firebase_admin import credentials
from pathlib import Path
import json

service_account_filepath = Path(__file__).parent.joinpath("service.json")
cred = credentials.Certificate(service_account_filepath)
app = firebase_admin.initialize_app(cred)
auth = auth.get_oidc_provider_config("oidc.google.com", app)
this_dir = Path(__file__).parent

firebase_config_file = this_dir.joinpath("firebase.json")
firebase_config : dict = {}
with open(firebase_config_file, 'r') as file :
  firebase_config = json.load(file)

app = firebase_admin.initialize_app()
