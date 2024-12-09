#include <assert.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <atomic>
// #include "board.h"
using namespace std;

pthread_barrier_t bar;

int currentPlayer = 1;
const int rows = 7, columns = 7;
int board[rows][columns] = {
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0}
};

const int* rowPointers[7][7] = {
    {&board[0][0], &board[0][1], &board[0][2], &board[0][3], &board[0][4], &board[0][5], &board[0][6]},
    {&board[1][0], &board[1][1], &board[1][2], &board[1][3], &board[1][4], &board[1][5], &board[1][6]},
    {&board[2][0], &board[2][1], &board[2][2], &board[2][3], &board[2][4], &board[2][5], &board[2][6]},
    {&board[3][0], &board[3][1], &board[3][2], &board[3][3], &board[3][4], &board[3][5], &board[3][6]},
    {&board[4][0], &board[4][1], &board[4][2], &board[4][3], &board[4][4], &board[4][5], &board[4][6]},
    {&board[5][0], &board[5][1], &board[5][2], &board[5][3], &board[5][4], &board[5][5], &board[5][6]},
    {&board[6][0], &board[6][1], &board[6][2], &board[6][3], &board[6][4], &board[6][5], &board[6][6]},
};

const int* colPointers[7][7] = {
    {&board[0][0], &board[1][0], &board[2][0], &board[3][0], &board[4][0], &board[5][0], &board[6][0]},
    {&board[0][1], &board[1][1], &board[2][1], &board[3][1], &board[4][1], &board[5][1], &board[6][1]},
    {&board[0][2], &board[1][2], &board[2][2], &board[3][2], &board[4][2], &board[5][2], &board[6][2]},
    {&board[0][3], &board[1][3], &board[2][3], &board[3][3], &board[4][3], &board[5][3], &board[6][3]},
    {&board[0][4], &board[1][4], &board[2][4], &board[3][4], &board[4][4], &board[5][4], &board[6][4]},
    {&board[0][5], &board[1][5], &board[2][5], &board[3][5], &board[4][5], &board[5][5], &board[6][5]},
    {&board[0][6], &board[1][6], &board[2][6], &board[3][6], &board[4][6], &board[5][6], &board[6][6]}
};

// size 7 diagonals
const int* dPointers1[2][7] = {
    {&board[0][0], &board[1][1], &board[2][2], &board[3][3], &board[4][4], &board[5][5], &board[6][6]},
    {&board[6][0], &board[5][1], &board[4][2], &board[3][3], &board[2][4], &board[1][5], &board[0][6]}
};  

// size 6 diagonals
const int* dPointers2[4][6] = {
    {&board[0][1], &board[1][2], &board[2][3], &board[3][4], &board[4][5], &board[5][6]},
    {&board[1][0], &board[2][1], &board[3][2], &board[4][3], &board[5][4], &board[6][5]},
    {&board[0][5], &board[1][4], &board[2][3], &board[3][2], &board[4][1], &board[5][0]},
    {&board[1][6], &board[2][5], &board[3][4], &board[4][3], &board[5][2], &board[6][1]}
};

// size 5 diagonals
const int* dPointers3[4][5] = {
    {&board[0][2], &board[1][3], &board[2][4], &board[3][5], &board[4][6]},
    {&board[2][0], &board[3][1], &board[4][2], &board[5][3], &board[6][4]},
    {&board[0][4], &board[1][3], &board[2][2], &board[3][1], &board[4][0]},
    {&board[2][6], &board[3][5], &board[4][4], &board[5][3], &board[6][2]}
};

// size 4 diagonals
const int* dPointers4[4][4] = {
    {&board[0][3], &board[1][2], &board[2][1], &board[3][0]},
    {&board[0][3], &board[1][4], &board[2][5], &board[3][6]},
    {&board[3][0], &board[4][1], &board[5][2], &board[6][3]},
    {&board[3][6], &board[4][5], &board[5][4], &board[6][3]}
};

const int** pointers[28] = {
    rowPointers[0], rowPointers[1], rowPointers[2], rowPointers[3], rowPointers[4], rowPointers[5], rowPointers[6],
    colPointers[0], colPointers[1], colPointers[2], colPointers[3], colPointers[4], colPointers[5], colPointers[6],
    dPointers1[0], dPointers1[1],
    dPointers2[0], dPointers2[1], dPointers2[2], dPointers2[3],
    dPointers3[0], dPointers3[1], dPointers3[2], dPointers3[3],
    dPointers4[0], dPointers4[1], dPointers4[2], dPointers4[3]
};

const int lengths[28] = {
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,  
    6, 6, 6, 6,                                      
    5, 5, 5, 5,                                       
    4, 4, 4, 4                                        
};

atomic<bool> endGame(false);

int toInt(char);
void display();
bool drop(int);
void verifyInput(char&);
void checkLine(const int**, int);


class Task{
    int id;
    int ntasks;
    const int** assigned;
    int N;
public:
    Task(int id, const int ntasks, const int** assigned, int N) : id(id), ntasks(ntasks), assigned(assigned), N(N){}

    static void* runner(void* arg){
        reinterpret_cast<Task*>(arg)->execute();
        return nullptr;
    }

    void execute(){
        checkLine(assigned, N);
        
        if(endGame.load())
            return;
    }
};

int checkBoard(std::vector<Task>);

int main(){
    

    const int ntasks = 28; 
    pthread_t threads[ntasks];

    std::vector<Task> tasks;
    for(int i = 0; i < ntasks; i++)
        tasks.emplace_back(i, ntasks, pointers[i], lengths[i]);

    //do{
        display();
        std::cout << "Player " << currentPlayer << ", it is your turn...\n";
        currentPlayer = (currentPlayer == 2) + 1; // if player 1, sets to 0+1. if player 2 sets to 1+1
    //}while(!endGame.load());

    // checkBoard(tasks);
    
    return 0;
}

int toInt(char column){
    return column - 'A';
}

void display() {
    char symbol = ' ';
    for (int i = rows - 1; i >= 0; --i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == 1) symbol = 'X';
            else if (board[i][j] == 2) symbol = 'O';
            else symbol = '-';
            std::cout << symbol << " ";
        }
        std::cout << "\n";
    }
    std::cout << "-------------\n";
    std::cout << "A B C D E F G\n";
}

void verifyInput(char &ch){
    bool flag;
    do{
        flag = true;
        if(ch >= 'A' && ch == 'G')
            flag = false;
        else{
            std::cerr << "That is an invalid row, try again." << std::endl;
            std::cin >> ch;
            ch = toupper(ch);
        }
    }while(flag);
}

bool drop(int column){
    if(board[6][column] != 0){
        std::cerr << "This column is full, try again." << std::endl;
        return false;
    }
    
    for(int i = 0; i < rows; i++){
        if(board[i][column] != 0){
            board[i][column] = currentPlayer;
            return true;
        }
    }
    return false;
}

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

int checkBoard(std::vector<Task> tasks){
    pthread_barrier_init(&bar, nullptr, tasks.size());
    
    std::vector<pthread_t> threads(tasks.size());

    int status;
    for(int i=0; i < tasks.size(); ++i) {
        status = ::pthread_create(&threads[i], nullptr, Task::runner, &tasks[i]);

        if (status != 0) {
            ::perror("thread create");
            return 1;
        }
    }

    for (int i = 0; i < tasks.size(); ++i) {
        pthread_join(threads[i], nullptr);
    }

    pthread_barrier_destroy(&bar);

    return 0;
}