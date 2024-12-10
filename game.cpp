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
#include "resources.h"
using namespace std;

pthread_barrier_t bar;

int currentPlayer = 1;

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