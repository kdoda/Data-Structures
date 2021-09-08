###############################################################
# Program:
#     Week 03, QUEUE
#     Brother Ercanbrack, CS235
# Author:
#     Klevin Doda
# Summary:
#     I created the ADT queue and the program to interact with
#     the user to see and buy stocks
# Time:
#     4 h
###############################################################

##############################################################
# The main rule
##############################################################
a.out: queue.h week03.o dollars.o stock.o
	g++ -o a.out week03.o dollars.o stock.o -std=c++11
	tar -cf week03.tar *.h *.cpp makefile

dollarsTest: dollars.o dollarsTest.cpp
	g++ -o dollarsTest dollars.o dollarsTest.cpp -std=c++11

##############################################################
# The individual components
#      week03.o       : the driver program
#      dollars.o      : the Dollars class
#      stock.o        : the logic for the stock program
##############################################################
week03.o: queue.h week03.cpp
	g++ -c week03.cpp -std=c++11

dollars.o: dollars.h dollars.cpp
	g++ -c dollars.cpp -std=c++11

stock.o: stock.h stock.cpp queue.h
	g++ -c stock.cpp -std=c++11
