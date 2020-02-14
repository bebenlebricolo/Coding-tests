#!/usr/bin/python3

import second
import third
import subdir.sub1

def main():
    second.second()
    third.third()
    second.second_calling_third()
    subdir.sub1.sub1()

main()