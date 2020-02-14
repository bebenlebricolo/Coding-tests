#!/usr/bin/python3

def second() :
    print("second")

def second_calling_third():
    print("second calling third")

# self test
if(__name__ == "__main__") :
   second()
   second_calling_third()