all:
	g++ main.cpp -std=c++11 -o main

open:
	g++ main.cpp -std=c++11 -o main
	./main main.cpp
