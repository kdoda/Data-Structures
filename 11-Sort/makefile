###############################################################
# Program:
#     Week 11, Sorts
#     Brother Ercanbrack, CS235
# Author:
#			Klevin Doda
# Summary:
#     This program will complete a heap merge and merge sort
#     on files filled with intergers.
# Time:
#     8h
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week11.o
	g++ -o a.out week11.o -std=c++11
	tar -cf week11.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week11.o     : the driver program
##############################################################
week11.o: merge.h heap.h week11.cpp
	g++ -c week11.cpp -std=c++11
##############################################################
# Makes clean
##############################################################
clean:
	rm a.out *.o *.tar
all : a.out
