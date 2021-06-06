all: main

main: main.cpp Fork.cpp Philosopher.cpp Table.cpp States.cpp
	g++ -std=c++17 -pthread -Wall *.cpp -o main -lncurses && ./main

clear:
	rm main
