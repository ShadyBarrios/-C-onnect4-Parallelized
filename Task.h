#ifndef _TASK_H_
#define _TASK_H_
#include <atomic>
using namespace std;

extern atomic<bool> endGame;
extern int winner;

extern void checkLine(const int**, int);

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

    void execute();
};

#endif