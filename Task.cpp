#include "Task.h"

atomic<bool> endGame(false);

void checkLine(const int** line, int size, int id) {
    int count = 1;
    winner = 0;

    for (int i = 1; i < size; ++i) {
        if (*line[i] == *line[i - 1] && *line[i] != 0) {
            ++count;
            if (count == 4) {
                endGame = true;
            }
        } else {
            count = 1;
        }
    }
}

void Task::execute(){
    checkLine(assigned, N, id);
}