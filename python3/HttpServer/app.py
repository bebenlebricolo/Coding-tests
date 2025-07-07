import json
from typing import cast
from flask import Flask, jsonify, request, Request, Response

app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def hello_world() :
    headers = request.headers
    if "toto" in headers :
        totoheader = headers["toto"]
        print(totoheader)

    # Check arguments as well
    args = request.args
    print(f"args = {args}")

    if "apikey" in args:
        apikey = args.get("apikey")
        print(f"Found apikey : {apikey}")
    else :
        data = {
            "Reason" : "Forbidden"
        }
        return Response(json.dumps(data), status=403, mimetype="application/json")


    data  = request.get_data().decode()
    print(data)
    return "Hello World!"