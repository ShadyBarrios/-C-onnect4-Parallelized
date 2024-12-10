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
#include "resources.h"
#include "Task.h"
using namespace std;

pthread_barrier_t bar;

int currentPlayer = 1;
int winner = 0;
char colSelection;
int intSelection;
bool validInput;

int toInt(char);
void display();
void displayRaw();
bool drop(int);
void verifyInput(char&);
bool checkBoard(std::vector<Task>);

int main(){
    const int ntasks = 28; 
    pthread_t threads[ntasks];

    std::vector<Task> tasks;
    for(int i = 0; i < ntasks; i++)
        tasks.emplace_back(i, ntasks, pointers[i], lengths[i]);

    endGame = false;

    for(;;){
        display();
        std::cout << "Player " << currentPlayer << ", it is your turn...\n";
        validInput = true;

        do{
            std::cout << "Select a column: ";
            std::cin >> colSelection;
            verifyInput(colSelection);
            intSelection = toInt(colSelection);
            validInput = drop(intSelection);
        }while(!validInput);

        checkBoard(tasks);
        if(endGame){
            winner = currentPlayer;
            break;
        }
        currentPlayer = (currentPlayer == 1) + 1; // if player 1, sets to 0+1. if player 2 sets to 1+1
    }

    display();
    cout << "Player " << winner << " has won! Congratulations!" << endl;
    
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

void displayRaw() {
    char symbol = ' ';
    for (int i = rows - 1; i >= 0; --i) {
        for (int j = 0; j < columns; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "-------------\n";
    std::cout << "A B C D E F G\n";
}

void verifyInput(char &ch){
    bool valid;
    ch = toupper(ch);

    do{
        valid = (ch >= 'A' && ch <= 'G');

        if(!valid){
            std::cerr << "That is an invalid row, try again: ";
            std::cin >> ch;
            ch = toupper(ch);
        }
    }while(!valid);
}

bool drop(int column){
    if(board[6][column] != 0){
        std::cerr << "This column is full, try again." << std::endl;
        return false;
    }
    
    for(int i = 0; i < rows; i++){
        if(board[i][column] == 0){
            board[i][column] = currentPlayer;
            return true;
        }
    }
    return false;
}

bool checkBoard(std::vector<Task> tasks){
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