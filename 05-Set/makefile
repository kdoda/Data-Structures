###############################################################
# Program:
#     Week 05, SET
#     Brother Ercanbrack, CS235
# Author:
#     Klevin Doda
# Summary:
#     Built the SET ADT, implemented by a sorted array,	also
#     build a program that would allow use to play gofish game.
# Time:
#     4 h
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week05.o goFish.o card.o
	g++ -o a.out week05.o goFish.o card.o -std=c++11
	tar -cf week05.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week05.o       : the driver program
#      goFish.o       : the logic for the goFish game
#      card.o         : a single playing card
##############################################################
week05.o: set.h goFish.h week05.cpp
	g++ -c week05.cpp -std=c++11

goFish.o: set.h goFish.h goFish.cpp card.h
	g++ -c goFish.cpp -std=c++11

card.o: card.h card.cpp
	g++ -c card.cpp -std=c++11
