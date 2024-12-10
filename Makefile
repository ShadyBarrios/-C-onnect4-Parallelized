.PHONY: board

board: game.cpp resources.cpp Task.cpp
	g++ -std=c++11 game.cpp Task.cpp resources.cpp -o board -pthread

game: board
	./board