#!/env/python

import sys
import argparse

def setup_parser() :
    parser = argparse.ArgumentParser()
    parser.add_argument("--option1", required=True)
    parser.add_argument("--option2", required=False)
    return parser


def main():
    parser = setup_parser()
    args = parser.parse_args(sys.argv[1:])

    option1 = "default1"
    option2 = "default2"

    if args.option1 is not None:
        option1 = args.option1
    if args.option2 is not None :
        option2 = args.option2

    print("Option 1 content is : \n" + option1)
    print("Option 2 content is : \n" + option2)

if __name__ == "__main__" :
    main()