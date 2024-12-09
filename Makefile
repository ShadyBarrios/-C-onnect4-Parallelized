.PHONY: board

board: game.cpp
	g++ -std=c++11 game.cpp -o board -pthread

game: board
	./board