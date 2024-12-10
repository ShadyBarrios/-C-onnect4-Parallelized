#include "Task.h"

atomic<bool> endGame(false);

void checkLine(const int** line, int size) {
    int count = 1;
    for (int i = 1; i < size; ++i) {
        if (*line[i] == *line[i - 1] && *line[i] != 0) {
            ++count;
            if (count == 4) endGame = true;
        } else {
            count = 1;
        }
    }
    endGame = false;
}

void Task::execute(){
    checkLine(assigned, N);
    
    if(endGame.load())
        return;
}