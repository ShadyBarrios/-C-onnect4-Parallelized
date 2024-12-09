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
// #include "board.h"

pthread_barrier_t bar;

int currentPlayer = 1;
const int rows = 7, columns = 7;
int board[rows][columns] = 
    {
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0}
    };

int toInt(char);
void display();
bool drop(int);
void verifyInput(char&);

class Task{
    int id;
    int ntasks;
    int* to;
    int* from;
    int N;
    int steps;
public:
    Task(int id, int tasks, int* to, int* from) : id(id), ntasks(ntasks), to(to), from(from){}
    static void* runner(void* arg){
        reinterpret_cast<Task*>(arg)->execute();
        return nullptr;
    }

    void execute(){
        int start;
        int end;
    }
};


int main(){
    return 0;
}

int toInt(char column){
    switch(column){
        case 'A': return 0;
        case 'B': return 1;
        case 'C': return 2;
        case 'D': return 3;
        case 'E': return 4;
        case 'F': return 5;
        case 'G': return 6;
    }
}

void verifyInput(char &ch){
    bool flag;
    do{
        flag = true;
        if(ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D' || ch == 'E' || ch == 'F' || ch == 'G')
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
}