###############################################################
# Program:
#     Week 01, Vector
#     Brother Ercanbrack, CS235
# Author:
#     Klevin Doda
# Summary:
#     Vector class implemented by C arrays, that can resize 
#     when they get full
# Time:
#     30 min
###############################################################

##############################################################
# The main rule
##############################################################
a.out: vector.h week01.o
	g++ -o a.out week01.o 
	tar -cf week01.tar vector.h week01.cpp makefile

##############################################################
# The individual components
#      week01.o     : the driver program
##############################################################
week01.o: vector.h week01.cpp
	g++ -c week01.cpp
