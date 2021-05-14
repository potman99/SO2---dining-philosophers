all: main

main: main.cpp Chopstick.cpp Philosopher.cpp Table.cpp
	g++ -std=c++14 -pthread -Wall *.cpp -o main -lncurses && ./main

clear:
	rm main
