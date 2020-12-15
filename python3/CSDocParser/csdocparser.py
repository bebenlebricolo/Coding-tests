#!/bin/python3

import os
import sys

from os import listdir, path
from os.path import isdir, join
from os import walk
from enum import Enum

import re
from cscomments import CSCommentParser

# Lists all necessary using statements for those modifications to work well
necessary_using_statements = ["using System;", "using System.ComponentModel;"]

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
    for dirpath, _ , files in walk(foldername) :
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

def is_doc_comment(line : str):
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
    for _ in range(0, padding):
        out += ' '
    return out

# a sample of CSharp keywords
CSharpKeywords = [
    "namespace",
    "public",
    "private",
    "protected",
    "abstract",
    "interface",
    "internal",
    "sealed",
    "class",
    "struct",
]

class DocumentationBlock :
    def __init__(self) :
        self.has_obs_tag = False        # If this block has the [Obsolete] documentation tag
        self.has_obs_attr = False       # If this block has the [Obsolete("lmqjdshgmqj")] attribute
        self.start_line = 0             # starting line index
        self.end_line = 0               # ending line index
        self.needs_editor_attr = True   # Tells whether this block needs the editorbrowsable attribute
        self.content = list()           # documentation block content

    def add_line(self, line : str) :
        self.content.append(line)

class ModifiedContent :
    class Kind(Enum) :
        ObsoleteTag =       "/// [Obsolete]\n"
        SeeCrefTag =        "/// This API is deprecated, <see cref=\"Placeholder.namespace\"/>\n"
        ObsoleteAttribute = "[Obsolete(\"Obsolete in date A, will be removed in date B\")]\n"
        EditorAttribute =   "[EditorBrowsable(EditorBrowsableState.Never)]\n"

    def __init__(self, line_count : int, content : Kind, padding : int) :
        self.line_count = line_count
        self.content = content
        self.padding = padding

    def generate(self):
        return generate_padding(self.padding) + self.content.value

class ModifiedBlock :
    def __init__(self):
        self.content = list()
        self.editor_browsable_found = False

class CsDocParser :
    class Mode(Enum):
        Normal = 0
        Block = 1
        EditorTagSearch = 2
        UsingStatements = 3

    class CSFile:
        def __init__(self, filepath, required_using):
            self.file = filepath
            self.parsed_using = list()      # list of using statements found in the parsed file
            self.req_using = required_using # list of required using
            self.last_using_line = 0        # Stores the last using statement line index

    def __init__(self, file ):
        self.csfile = self.CSFile(file,
                                  necessary_using_statements)   # Keeps track of the parsed file with special handling for using statements
        self.parsing_mode = self.Mode.UsingStatements           # Parsing mode (fed into the parsing state machine)
        self.docblock = DocumentationBlock()                    # Currently parsed documentation block
        self.data = list()                                      # list of DocumentationBlock
        self.parser = CSCommentParser()
        self.using_re_pattern = re.compile(r"using ([a-zA-Z]+[\.]*)+;")

    def parse(self):
        if os.path.isfile(self.csfile.file) and self.tryopen(self.csfile.file) :
            with open(self.csfile.file, 'r') as target_file:
                line_count = 0
                while True:
                    line = target_file.readline()
                    if not line :
                        if len(self.data) != 0 and self.data[-1].editor_browsable_found == False :
                            last_block = self.data[-1]
                            last_line_count = last_block.content[-1].line_count
                            last_padding = last_block.content[-1].padding
                            last_block.content.append(ModifiedContent(last_line_count, ModifiedContent.Kind.EditorAttribute, last_padding))
                        break

                    # Parse the line and store data about it if it matches some patterns
                    self.parse_line(line, line_count)
                    line_count += 1

    def handles_using_parsing(self, line : str , line_count : int) :
        match = re.search(self.using_re_pattern, line)
        if match is not None :
            self.csfile.parsed_using.append(line)
            self.csfile.last_using_line = line_count
        else :
            has_keyword = False
            for keyword in CSharpKeywords :
                if line.find(keyword) != -1:
                    has_keyword = True
                    break

            # Get back to normal parsing, no more using might be found in the file
            if has_keyword :
                self.parsing_mode = self.Mode.Normal


    def parse_line(self, line : str, line_count : int):
        is_doc = is_doc_comment(line)
        padding = resolve_padding(line)

        stripped_line = self.parser.parse_line(line, remove_comment=True).rstrip()

        # Focuses on the "using statements"
        # we use the stripped line because we don't want to parse using statements that are commented out!
        if self.parsing_mode == self.Mode.UsingStatements :
            self.handles_using_parsing(stripped_line, line_count)

        # Parse comments if any (starting/closing)
        elif self.parsing_mode == self.Mode.Normal :
            # Found block comment starting !
            if is_doc and line.find("<summary>") != -1 :
                self.parsing_mode = self.Mode.Block

                # before switching to block comment, check if last block had its editor browsable state
                if len(self.data) != 0 and self.data[-1].editor_browsable_found == False:
                    last_block = self.data[-1]
                    last_line_count = last_block.content[-1].line_count
                    last_padding = last_block.content[-1].padding
                    last_block.content.append(ModifiedContent(last_line_count, ModifiedContent.Kind.EditorAttribute, last_padding))

                new_block = ModifiedBlock()
                new_block.content.append(ModifiedContent(line_count + 1, ModifiedContent.Kind.ObsoleteTag, padding))
                # As this is a new insert, there is no need to do line_count +1 as we already have inserted one line before
                # So the +1 is justified (same as above)
                new_block.content.append(ModifiedContent(line_count + 1, ModifiedContent.Kind.SeeCrefTag, padding))
                self.data.append(new_block)

            elif line.find("EditorBrowsableState.Never") != -1 and len(self.data) != 0:
                self.data[-1].editor_browsable_found = True

        # Block parsing triggered
        # Stop block parsing whenever lines are not commented anymore
        elif not is_doc :
            if self.parsing_mode == self.Mode.Block :
                self.data[-1].content.append(ModifiedContent(line_count, ModifiedContent.Kind.ObsoleteAttribute, padding))

                if line.find("EditorBrowsableState.Never") != -1 and len(self.data) != 0:
                    self.data[-1].editor_browsable_found = True

                self.parsing_mode = self.Mode.Normal

    def resolve_needed_using(self) :
        self.csfile.req_using = list()
        for using in necessary_using_statements :
            if not using in self.csfile.parsed_using :
                self.csfile.req_using.append(using)


    def apply_modifications(self, duplicate : bool) :
        outfilename = os.path.basename(self.csfile.file)
        file_directory = os.path.dirname(self.csfile.file)
        if duplicate :
            outfilename = outfilename.split(".cs")[0]
            outfilename = outfilename + "_mod.cs"
        outfile = os.path.join(file_directory, outfilename)

        filecontent = {}
        with open(self.csfile.file, 'r') as target_file :
            filecontent = target_file.readlines()

        added_lines = 0

        # Handles using System; import
        self.resolve_needed_using()
        if len(self.csfile.req_using) != 0 :
            added_using = 0
            for using in self.csfile.req_using :
                filecontent.insert(self.csfile.last_using_line + added_using, using + "\n")
                added_lines += 1

        for modified_content in self.data :
            for new_line in modified_content.content :
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


"""@brief checks if the --duplicate option is part of the command line input
   @param args : list of arguments parsed from command line
"""
def has_duplicate_option(args) :
    for arg in args :
        if arg == "-d" or arg == "--duplicate" :
            return True
    return False

def main(args):
    check_help(args)
    cs_files = list_cs_files_in_folder(args[1])
    needs_duplicate = has_duplicate_option(args)
    for csfile in cs_files :
        parser = CsDocParser(csfile)
        parser.parse()
        parser.apply_modifications(needs_duplicate)

if __name__ == "__main__" :
    main(sys.argv)