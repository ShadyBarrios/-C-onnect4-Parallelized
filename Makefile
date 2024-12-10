.PHONY: board

board: game.cpp resources.cpp
	g++ -std=c++11 game.cpp resources.cpp -o board -pthread

game: board
	./board