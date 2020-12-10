#!/bin/python3

import os
import sys

from os import listdir, path
from os.path import isdir, join
from os import walk
from enum import Enum

def print_help() :
    print("C# documentation obsoleter usage : ")
    print("  This tool is capable of parsing block documentation comments from C# files and insert")
    print("  [Obsolete] tags and a reason for obsoleting its API.\n")

    print("  Usage :")
    print("  >> python3 csdocparser.py <directory> FLAGS ")
    print("     [ARGS] :")
    print("       directory : the directory which will be analysed.")
    print("                   All C# files in this directory will be modified ")
    print("     [FLAGS] :")
    print("       -h,--help      : Prints this help section ")
    print("       -d,--duplicate : All modified files will be duplicated like so : <filename>_mod.cs ")
    print("\n Note : cwd is {}".format(os.curdir))
    exit(1)

def check_help(args) :
    """Checks input to see if help was requested """
    needs_help = False
    # Checks arguments to see if help is requested
    for arg in args :
        if arg == "-h" or arg == "--help" :
            needs_help = True

    if needs_help :
        print_help()


def list_cs_files_in_folder( foldername ):
    """ Iterates over the given folder and tries to list all available xml files"""
    foldername = os.path.realpath(foldername)
    if not isdir(foldername) :
        print("Given foldername could not be resolved in the current scope, aborting.")
        print_help()

    cs_files = list()
    for dirpath, subdirs, files in walk(foldername) :
        for file in files :
            if file.endswith(".cs") :
                relative_path = join(dirpath, file)
                cs_files.append(os.path.abspath(relative_path))
    if cs_files.count == 0 :
        print("Could not find C# files within the given directory.")
        print_help()

    return cs_files

def resolve_padding(line:str):
    padding = 0
    for char in line :
        if char == ' ' :
            padding += 1
        else:
            break
    return padding

def is_line_comment(line : str):
    if line.find("///") == -1 :
        return False
    else :
        return True

def is_using_statement(line : str):
    if line.find("using") == -1 :
        return False
    else :
        return True

def generate_padding(padding : int):
    out = str()
    for i in range(0, padding):
        out += ' '
    return out

class ModifiedContent :
    class Kind(Enum) :
        ObsoleteTag = "/// [Obsolete]\n"
        ObsoleteAttribute = "[Obsolete(\"Obsolete in 2021.1, will be removed in 2022.1\")]\n"
        EditorAttribute = "[System.ComponentModel.EditorBrowsable(System.ComponentModel.EditorBrowsableState.Never)]\n"

    def __init__(self, line_count : int, content : Kind, padding : int) :
        self.line_count = line_count
        self.content = content
        self.padding = padding

    def generate(self):
        return generate_padding(self.padding) + self.content.value

class CsDocParser :
    class Mode(Enum):
        Normal = 0
        Block = 1
        EditorTagSearch = 2

    def __init__(self, file):
        self.file = file
        self.parsing_mode = self.Mode.Normal
        self.data = list()
        self.needs_using_system = True # Tells whether the locally inspected file needs the using System; import
        self.using_block_start = -1

    def parse(self):
        if os.path.isfile(self.file) and self.tryopen(self.file) :
            with open(self.file, 'r') as target_file:
                line_count = 0
                while True:
                    line = target_file.readline()
                    if not line :
                        break

                    # Parse the line and store data about it if it matches some patterns
                    self.parse_line(line, line_count)
                    line_count += 1

    def parse_line(self, line : str, line_count : int):
        is_comment = is_line_comment(line)
        padding = resolve_padding(line)

        # Parse comments if any (starting/closing)
        if self.parsing_mode == self.Mode.Normal :
            # Found block comment starting !
            if is_comment and line.find("<summary>") != -1 :
                self.parsing_mode = self.Mode.Block
                self.data.append(ModifiedContent(line_count + 1, ModifiedContent.Kind.ObsoleteTag, padding))

        # Block parsing triggered
        # Stop block parsing whenever lines are not commented anymore
        elif not is_comment :
            if self.parsing_mode == self.Mode.Block :
                self.parsing_mode = self.Mode.EditorTagSearch
                self.data.append(ModifiedContent(line_count, ModifiedContent.Kind.ObsoleteAttribute, padding))

            # Check for EditorBrowsable attribute
            elif self.parsing_mode == self.Mode.EditorTagSearch :
                search_lines_count = (line_count - self.data[-1].line_count)
                # Do not trigger attribute addition if one is found within 5 lines after switching off
                # comment parsing
                if search_lines_count < 3 :
                    if line.find("System.ComponentModel.EditorBrowsableState.Never") != -1 :
                        self.parsing_mode = self.Mode.Normal
                else :
                    self.parsing_mode = self.Mode.Normal
                    last_line_count = self.data[-1].line_count
                    last_padding = self.data[-1].padding
                    self.data.append(ModifiedContent(last_line_count, ModifiedContent.Kind.EditorAttribute, last_padding))

        if is_using_statement(line) :
            # Record where using block starts
            if self.using_block_start == -1 :
                self.using_block_start = line_count

            if line.find("using System;") != -1 :
                self.needs_using_system = False

    def apply_modifications(self, duplicate : bool) :
        outfilename = os.path.basename(self.file)
        file_directory = os.path.dirname(self.file)
        if duplicate :
            outfilename = outfilename.split(".cs")[0]
            outfilename = outfilename + "_mod.cs"
        outfile = os.path.join(file_directory, outfilename)

        filecontent = {}
        with open(self.file, 'r') as target_file :
            filecontent = target_file.readlines()

        added_lines = 0

        # Handles using System; import
        if self.needs_using_system :
            if self.using_block_start == -1 :
                self.using_block_start = 0

            filecontent.insert(self.using_block_start, "using System;\n")
            added_lines += 1

        for new_line in self.data :
            filecontent.insert(new_line.line_count + added_lines, new_line.generate())
            added_lines += 1

        with open(outfile, 'w') as out :
            out.writelines(filecontent)



    def tryopen(self, file):
        canopen = True
        try :
            testfile = open(file, 'r')
        except Exception as e :
            print("Could not open file : {}".format(e))
            canopen = False
        finally:
            if not testfile.closed :
                testfile.close()
        return canopen


def main(args):
    check_help(args)
    cs_files = list_cs_files_in_folder(args[1])
    needs_duplicate = False
    if len(args) > 2 :
        needs_duplicate = (args[2] == "-d") or (args[2] == "--duplicate")
    for csfile in cs_files :
        parser = CsDocParser(csfile)
        parser.parse()
        parser.apply_modifications(needs_duplicate)

if __name__ == "__main__" :
    main(sys.argv)