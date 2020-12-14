import sys
from enum import Enum

def find_in(string : str, pattern : str) :
    indexes = list()
    found = -len(pattern)
    while found != -1:
        found = string.find(pattern, found + len(pattern))
        if found != -1 :
            indexes.append(found)

    if len(indexes) == 0 :
        indexes.append(-1)
    return indexes


class CSCommentParser :
    class Type(Enum) :
        NoComment = ""
        Line = "//"
        BlockOpen = "/*"
        BlockEnd = "*/"

    class Mode(Enum):
        Normal = 0
        Single = 1
        Block = 2

    class MarkerPair:
        def __init__(self, type, index):
            self.type = type
            self.index = index

    def __init__(self):
        self.mode = self.Mode.Normal

    def accumulate(self, markers_list, type, indexes):
        if indexes[0] == -1:
            return markers_list

        for index in indexes :
            markers_list.append(self.MarkerPair(type, index))
        return markers_list

    def parse_comments_markers(self, line : str):
        markers = list()
        single_comments = find_in(line, self.Type.Line.value)
        block_op = find_in(line, self.Type.BlockOpen.value)
        block_end = find_in(line, self.Type.BlockEnd.value)

        markers = self.accumulate(markers, self.Type.Line, single_comments)
        markers = self.accumulate(markers, self.Type.BlockOpen, block_op)
        markers = self.accumulate(markers, self.Type.BlockEnd, block_end)
        markers = sorted(markers, key=lambda obj : obj.index)

        return markers

    def find_next_block_end(self, markers, current_index) :
        for m_index in range(current_index, len(markers)):
            if markers[m_index].type == self.Type.BlockEnd:
                return {"index" : m_index, "marker" : markers[m_index]}
        return None

    def parse_line(self, line : str, remove_comment=True):
        markers = self.parse_comments_markers(line)
        out = line
        if self.mode == self.Mode.Normal :
            if len(markers) != 0 :
                # Iterate over the markers
                character = markers[0].type
                c_index = markers[0].index

                # Single line comments are popped out directly : everything which is at the right of those comments is stripped away
                if character == self.Type.Line :
                    if remove_comment :
                       out = line[0 : c_index]

                # In case of comment block opening /*, check for the counterpart */.
                # If closing comment marker is not found, then we switch to the block parsing mode to be able to interprete incoming
                # lines.
                # Otherwise, if closing block marker is found, remove the enclosed part from the line and if that marker was not the last marker
                # on this line, recurse with the remaining part of the line
                elif character == self.Type.BlockOpen :
                    next_end = self.find_next_block_end(markers, 1)
                    if next_end is None :
                        self.mode = self.Mode.Block
                        if remove_comment :
                            out = line[0 : c_index]
                    else :
                        if next_end["index"] == (len(markers) - 1) :
                            before = line[0 : c_index]
                            after = line[next_end["marker"].index + len(self.Type.BlockEnd.value) : len(line)]
                            if remove_comment :
                                out = before + after
                        else :
                            # Recurse on itself to pop out the last bits of the comments in line
                            before = line[0 : c_index]
                            if remove_comment :
                                out = before + self.parse_line(line[next_end["marker"].index + len(self.Type.BlockEnd.value) : len(line)], remove_comment)

        # Research the next BlockEnd character
        elif self.mode == self.Mode.Block :
            next_end = self.find_next_block_end(markers, 0)
            if next_end is None:
                if remove_comment :
                    out = ""
            else:
                self.mode = self.Mode.Normal
                after = line[next_end["marker"].index + len(self.Type.BlockEnd.value) : len(line)]
                if next_end["index"] == (len(markers) - 1) :
                    if remove_comment :
                        out = after
                else :
                    if remove_comment :
                        out = self.parse_line(after, remove_comment)

        return out


class tests :
    testcomments = [
        "// This is an inline comment",
        "namespace toto { // another inline comment",
        "/* namespace toto { */",
        "/* namespace toto {\n public class MyClass */",
        "/* namespace toto { // comment to be ignored */",
        "//comment \n/* namespace toto { */ class titi /* class tata */",  # Only "class titi" should be parsed
    ]

    def test_parse_markers_simple_inline(self):
        parser = CSCommentParser()
        markers = parser.parse_comments_markers(self.testcomments[0])
        assert(len(markers) == 1)
        assert(markers[0].type == CSCommentParser.Type.Line)
        assert(markers[0].index == 0)

    def test_parse_markers_simple_inline2(self):
        parser = CSCommentParser()
        markers = parser.parse_comments_markers(self.testcomments[1])
        assert(len(markers) == 1)
        assert(markers[0].type == CSCommentParser.Type.Line)
        assert(markers[0].index == 17)

    def test_parse_markers_block1(self):
        parser = CSCommentParser()
        markers = parser.parse_comments_markers(self.testcomments[2])
        assert(len(markers) == 2)
        assert(markers[0].type == CSCommentParser.Type.BlockOpen)
        assert(markers[0].index == 0)
        assert(markers[1].type == CSCommentParser.Type.BlockEnd)
        assert(markers[1].index == 20)

    def test_parse_markers_block2(self):
        parser = CSCommentParser()
        markers = parser.parse_comments_markers(self.testcomments[3])
        assert(len(markers) == 2)
        assert(markers[0].type == CSCommentParser.Type.BlockOpen)
        assert(markers[0].index == 0)
        assert(markers[1].type == CSCommentParser.Type.BlockEnd)
        assert(markers[1].index == 42)

    def test_parse_markers_block_single1(self):
        parser = CSCommentParser()
        markers = parser.parse_comments_markers(self.testcomments[4])
        assert(len(markers) == 3)

        expected_results = [
            CSCommentParser.MarkerPair(CSCommentParser.Type.BlockOpen, 0),
            CSCommentParser.MarkerPair(CSCommentParser.Type.Line, 20),
            CSCommentParser.MarkerPair(CSCommentParser.Type.BlockEnd, 45),
        ]

        for i in range(0, len(markers)) :
            marker = markers[i]
            expected_result = expected_results[i]
            assert(marker.type.value == expected_result.type.value)
            assert(marker.index == expected_result.index)

    def test_parse_markers_block_single2(self):
        parser = CSCommentParser()
        markers = parser.parse_comments_markers(self.testcomments[5])
        assert(len(markers) == 5)

        expected_results = [
            CSCommentParser.MarkerPair(CSCommentParser.Type.Line, 0),
            CSCommentParser.MarkerPair(CSCommentParser.Type.BlockOpen, 11),
            CSCommentParser.MarkerPair(CSCommentParser.Type.BlockEnd, 31),
            CSCommentParser.MarkerPair(CSCommentParser.Type.BlockOpen, 45),
            CSCommentParser.MarkerPair(CSCommentParser.Type.BlockEnd, 59),
        ]

        for i in range(0, len(markers)) :
            marker = markers[i]
            expected_result = expected_results[i]
            assert(marker.type.value == expected_result.type.value)
            assert(marker.index == expected_result.index)

    def test_remove_comments_simple_inline(self):
        parser = CSCommentParser()
        stripped = parser.parse_line(self.testcomments[0])
        assert(stripped == "")

    def test_remove_comments_simple_inline2(self):
        parser = CSCommentParser()
        stripped = parser.parse_line(self.testcomments[1])
        assert(stripped == "namespace toto { ")

    def test_remove_comments_block1(self):
        parser = CSCommentParser()
        stripped = parser.parse_line(self.testcomments[2])
        assert(stripped == "")

    def test_remove_comments_block2(self):
        parser = CSCommentParser()
        stripped = parser.parse_line(self.testcomments[3])
        assert(stripped == "")

    def test_remove_comments_mixed1(self):
        parser = CSCommentParser()
        stripped = parser.parse_line(self.testcomments[4])
        assert(stripped == "")

    def test_remove_comments_mixed2(self):
        parser = CSCommentParser()
        stripped = parser.parse_line(self.testcomments[5])
        assert(stripped == "")

    def test_remove_comments_mixed3(self):
        parser = CSCommentParser()
        stripped = parser.parse_line("namespace toto { /* something right here // comment */ public class titi")
        assert(stripped == "namespace toto {  public class titi")

    def test_remove_comments_mixed4(self):
        parser = CSCommentParser()
        stripped = parser.parse_line("namespace toto { /* something */ public class titi : /* another comment */ public Isomething // final comment")
        assert(stripped == "namespace toto {  public class titi :  public Isomething ")

    def test_remove_comments_multiline(self):
        parser = CSCommentParser()
        multiline_comment = [
            "namespace toto { /* something right here ",
            "public class tata; // Commented out",
            "public class titi; // Commented out",
            "*/public class tutu; // This is the class I want",
        ]

        expected_result = [
            "namespace toto { ",
            "",
            "",
            "public class tutu; ",
        ]

        result = list()
        for line in multiline_comment :
            result.append(parser.parse_line(line))

        for i in range(0, len(multiline_comment)):
            assert(expected_result[i] == result[i])

    def run_all_tests(self):
        self.test_parse_markers_simple_inline()
        self.test_parse_markers_simple_inline2()
        self.test_parse_markers_block1()
        self.test_parse_markers_block2()
        self.test_parse_markers_block_single1()
        self.test_parse_markers_block_single2()

        self.test_remove_comments_simple_inline()
        self.test_remove_comments_simple_inline2()
        self.test_remove_comments_block1()
        self.test_remove_comments_block2()
        self.test_remove_comments_mixed1()
        self.test_remove_comments_mixed2()
        self.test_remove_comments_mixed3()
        self.test_remove_comments_mixed4()

        self.test_remove_comments_multiline()

def run_tests():
    tests_obj = tests()
    tests_obj.run_all_tests()

def main(args):
    parser = CSCommentParser()
    stripped_lines = list()
    with open(args[1], 'r') as file :
        while True:
            line = file.readline()
            if not line :
                break
            stripped = parser.parse_line(line).rstrip()

            # if not empty, push append it
            if stripped :
                stripped_lines.append(parser.parse_line(line))


    with open("Tests/output.cs", 'w') as file :
        file.writelines(stripped_lines)

if __name__ == "__main__" :
    #run_tests()
    main(sys.argv)