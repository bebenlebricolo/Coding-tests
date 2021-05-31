#!/usr/bin/python3

import re
import sys
from pathlib import Path
import os

def print_help():
    print("\n=========================================================================")
    print("Wavefront obj python component inverter for Obj ASCII file format")
    print("=========================================================================\n")
    print("This script aims to invert one or several components of the input file (reverse its sign)")
    print("It expects a file as input, takes its basename and outputs the transformed file\n")
    print("  Usage : python3 obj_component_inverter.py <File> <Components> [OPTS : <outputfile>]")
    print("    + <File>         : input filepath, could either be relative or absolute")
    print("    + <Components>   : Components to be inverted. E.g : \"XYZ\" will invert all 3 components\n")
    print("    + FLAGS")
    print("      + [-h, --help] : Displays this help section\n")
    print("    + OPTS")
    print("      + [-o]         : Output filename. If given, this option will specify the converted output file")
    print("                       If not specified, output file will overwrite the source file\n")
    print("Example : ")
    print("    + python3 obj_component_inverter.py Horizon.obj X")
    print("    + python3 obj_component_inverter.py \"C:\\temp\\data\\Horizon.obj XY\" \n")


class Input :
    def __init__(self, infile = "", outfile = "", comps = ""):
        self.infile=infile
        self.outfile=outfile
        self.comps=comps

def invert_single_str(string_component : str) -> str:
    if string_component[0] == '-' :
        return string_component[1:]
    return "-" + string_component

def invert_component(comp_to_invert : str, line : str) -> str :
    # Remove double whitespaces
    line = re.sub(' +', ' ', line)
    components = line.split(' ')


    if comp_to_invert.capitalize().find('X') != -1:
        components[1] = invert_single_str(components[1])

    if comp_to_invert.capitalize().find('Y') != -1:
        components[2] = invert_single_str(components[2])

    if comp_to_invert.capitalize().find('Z') != -1:
        components[3] = invert_single_str(components[3])

    inverted_line = "{}   {} {} {}".format(components[0], components[1], components[2], components[3])
    return inverted_line


def parse_cmdline(argv):
    input = Input("", "", "")

    # Used to fuel the internal state machine when looking for -o option
    output_opt_found = False
    for arg in argv[1:]:
        if arg == "-o":
            output_opt_found = True
            continue

        # Extract output file
        if output_opt_found :
            input.outfile = arg
            output_opt_found = False

        # While we are at it, break on help if necessary
        if arg == "-h" or arg == "--help":
            print_help()
            exit(0)
    input.infile = argv[1]
    input.comps = argv[2]

    # Check input filepath
    if input.infile:
        infilepath = Path(input.infile).absolute()
        if not infilepath.exists():
            print("Input file does not exist. Aborting execution.")
            exit(1)

    return input

def main(argv) -> int :
    if len(argv) < 3:
        print("Too few arguments.")
        print_help()
        exit(0)

    input = parse_cmdline(argv)

    input_file = None
    try:
        input_file = open(input.infile, "r")
    except OSError as e:
        print("Could not open input file because : {}".format(e))
        return 1

    in_line=""
    out_lines_content = [""]
    while True:
        in_line = input_file.readline()
        # End of file reached
        if not in_line :
            break

        # Nothing to be done in such a case
        if len(in_line) == 0 or in_line == "\n":
            out_lines_content.append(in_line)
            continue

        # Drop comments and we don't want to invert face's reference indexes
        if in_line.find("#") == 0 or in_line.find("v") != 0:
            out_lines_content.append(in_line)
            continue

        out_line = invert_component(input.comps, in_line)
        out_lines_content.append(out_line)
    input_file.close()

    # If we have specified an output file
    # Write content to it, otherwise reopen input file in write mode and overwrite it
    output_file = None
    try:
        if input.outfile :
            output_file = open(input.outfile, "w")
        else:
            input_dir = Path(input.infile).absolute().parent
            filename = Path(input.infile).name.split(".")[0]
            input.outfile = Path.joinpath(input_dir, filename + "_inv.obj")
            output_file = open(input.outfile, "w")
    except OSError as e:
        print("Could not open output file because : {}".format(e))
        return 1
    output_file.writelines(out_lines_content)
    output_file.close()
    print("Successfully wrote all lines to file, exiting program")

    return 0


if __name__ == "__main__" :
    main(sys.argv)
