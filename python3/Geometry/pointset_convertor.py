#!/usr/bin/python3
import sys
import re
from pathlib import Path

def print_help():
    print("\n=========================================================================")
    print("PXYZ python convertor for Charisma 3D interpretation lines file format")
    print("=========================================================================\n")
    print("This script helps to convert input file using Charisma 3D interpretation lines (ASCII) format into a XYZ file")
    print("It expects a file as input, takes its basename and outputs the transformed file\n")
    print("  Usage : python3 pxyz_convertor.py <File>")
    print("    + <File> : input filepath, could either be relative or absolute\n")
    print("Example : ")
    print("    + python3 pxyz_convertor.py Horizon")
    print("    + python3 pxyz_convertor.py C:\\temp\\data\\Horizon\n")

def convert_file(file):
    filepath = Path(file)
    if not filepath.exists() and not Path(Path(file).absolute).exists():
        return "File does not exist"

    input_file = None
    output_file = None

    input_filename = filepath.name
    output_filename = input_filename + ".xyz"

    # Global open and try expect
    try:
        input_file = open(filepath, "r")
    except OSError as e:
        return "Could not open input file because : {}".format(e)

    try:
        output_file = open(output_filename, "w")
    except OSError as e:
        return "Could not open output file because : {}".format(e)

    in_line=""
    out_line=""
    while True:
        in_line = input_file.readline()
        # End of file reached
        if not in_line :
            break

        # Nothing to be done in such a case
        if len(in_line) == 0:
            continue

        in_line = re.sub(' +', ' ', in_line)
        blocks = in_line.split(' ')
        blocks= blocks[6:]
        blocks[2] = blocks[2].strip("\n")

        # Write the flat line interpretation to out_line
        out_line = ""
        index = 0
        for component in blocks:
            out_line += component
            if index != 2 :
                out_line += " "
            index += 1
        output_file.write(out_line + "\n")

    input_file.close()
    output_file.close()
    return "Successfully converted {} to {} !".format(input_filename, output_filename)

def main(argv):
    if len(argv) != 2:
        print_help()

    result = convert_file(argv[1])
    print(result)
    return 0

if __name__ == "__main__":
    main(sys.argv)