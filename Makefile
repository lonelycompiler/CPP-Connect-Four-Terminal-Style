all: ./src/connectfour.cpp ./src/connectfour.h
	clang++ ./src/connectfour.cpp -g -Wall -std=c++17 -o connectfour