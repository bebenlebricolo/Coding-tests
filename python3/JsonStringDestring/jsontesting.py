import json
import sys

#{
#    "blahblah": "topitop",
#    "toto": "titi",
#    "this is a block": {
#        "single member": true
#    },
#    "my custom array": [
#        {
#            "object name": "New object",
#            "kind": "ellipsis",
#            "eccentricity": 0.25,
#            "main axis" : 23.25,
#            "contour thickness" : 3
#        }
#    ]
#}

# "{\"blahblah\":\"topitop\",\"toto\":\"titi\",\"this is a block\":{\"single member\":true},\"my custom array\":[{\"object name\":\"New object\",\"kind\":\"ellipsis\",\"eccentricity\":0.25,\"main axis\":23.25,\"contour thickness\":3}]}"

jsonstring = sys.argv[1]
loaded_j = json.loads(jsonstring)

print("\n\n ----- Json loaded from command line looks like this : \n{}".format(loaded_j))
print("\n\n ----- Json dumped as a plain string looks like this : \n{}".format(json.dumps(loaded_j, ensure_ascii=True, indent=4)))