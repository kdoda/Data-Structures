###############################################################
# Program:
#     Week 13, GENEALOGY
#     Brother Ercanbrack, CS235
# Author:
#     Klevin Doda
# Summary:
#     Parsed the Gedcom file, stored them in a sorted LL, wrote 
#     them in a file and print the pedigree in the console.
#
#     For some reason Thomas Duncan is shifted two spaces on 
#     the left in the final2.out and not left aligned with 
#     other individuals. I tried all the combination
#     of setw and cout.width but it didn't work.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week13.o
	g++ -o a.out week13.o -g -std=c++11
	tar -cf week13.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week13.o     : the driver program
#      spellCheck.o   : the spell-check program and driver
##############################################################
week13.o: node.h week13.cpp vector.h person.h queue.h
	g++ -c week13.cpp -g -std=c++11


