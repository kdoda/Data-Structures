###############################################################
# Program:
#     Week 07, LIST
#     Brother Ercanbrack, CS235
# Author:
#     Klevin Doda
# Summary:
#     Build the List ADT implemented by a double linked list
#     Also created a WholeNumber class, which handles very 
#     large numbers. Used the WholeNumber to calculate the
#     nth Fibonachi number in O(n).
# Time:
#     10h
###############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h week07.o fibonacci.o
	g++ -o a.out week07.o fibonacci.o -std=c++11
	tar -cf week07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week07.o       : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      <anything else?>
##############################################################
week07.o: list.h week07.cpp
	g++ -c week07.cpp -std=c++11

fibonacci.o: fibonacci.h fibonacci.cpp list.h
	g++ -c fibonacci.cpp -std=c++11

