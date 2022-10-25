from flask import Flask, jsonify, request
import json

app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def hello_world() :
    data  = request.get_data().decode()
    print(data)
    return "Hello World!"