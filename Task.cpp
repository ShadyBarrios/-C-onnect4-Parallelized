#include "Task.h"

atomic<bool> endGame(false);

void checkLine(const int** line, int size) {
    int count = 1;
    int possibleWinner = 0;
    for (int i = 1; i < size; ++i) {
        if (*line[i] == *line[i - 1] && *line[i] != 0) {
            ++count;
            possibleWinner = line[i];
            if (count == 4) {
                return possibleWinner;
            }
        } else {
            count = 1;
        }
    }
    return 0;
}

void Task::execute(){
    checkLine(assigned, N);
    
    if(endGame.load())
        return;
}