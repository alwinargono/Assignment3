#ifndef PAGING_H
#define PAGING_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
//#include <utility>

using namespace std;

queue<int> myqueue;

struct process{
    int id;
    char action;	//input
    int page;		//input
    bool swap;
    bool killed;
    int pageAllocated;
    bool modified;
    bool terminated;
    bool created;
    int pageNum;
    int modNum;
    bool accessed;
    int vir;
    int phys;




//    int arrival;
//    int duration;
//    int startTime;
//    int endTime;
//    int tempDur;
//    int remaining;
//    bool running;
//    bool done;

    process(): id(-1),page(0), swap(0), killed(0), pageAllocated(0), modified(0),
    		terminated(0), created(0), pageNum(0), modNum(-1),vir(0),phys(0)
    {}
};

process copy1Struct(process arr)
{
	process newProc;
    newProc.id = arr.id;
    newProc.action = arr.action;
    newProc.page = arr.page;
    newProc.swap = arr.swap;
    newProc.killed = arr.killed;
    newProc.pageAllocated = arr.pageAllocated;
    newProc.modified = arr.modified;
    newProc.terminated = arr.terminated;
    newProc.created = arr.created;
    newProc.pageNum = arr.pageNum;
    newProc.modNum = arr.modNum;
    newProc.accessed = arr.accessed;
    newProc.vir = arr.vir;
    newProc.phys = arr.phys;

    return newProc;
}
process* copyStruct(process arr[], int startIndex, int endIndex)
{
    process* newProc = new process[endIndex-startIndex];
    for(int i = startIndex; i<endIndex; i++)
    {
        newProc[i].id = arr[i].id;
    }
    return newProc;
}

void printStruct(process arr[], int startIndex, int endIndex)
{
    for(int i = startIndex; i<endIndex; i++)
    {
        cout << "process id : " << arr[i].id << endl;
        cout << "process action : " << arr[i].action << endl;
        cout << "process page : " << arr[i].page << endl;
    }
    return;
}

void printStructInfo(process arr[], int startIndex, int endIndex)
{
    for(int i = startIndex; i<endIndex; i++)
    {
        cout << "process id : " << arr[i].id << endl;
    }
    return;
}

int minIndex(int arr[],int count)
{
    int temp;
    int j =0;

    for(int i = 0;i<count;i++)
    {
        j++;
        if(arr[i] > arr[j])
        {
            temp = j;
        }
    }
    return temp;
}

void swap(struct process *xp, struct process *yp)
{
    process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void LRU(process proc[], process newProc, process* swapArr)
{
    if(myqueue.empty())
    {
        for(int i = 0;i<20;i++)
        {
            myqueue.push(i);
        }
    }
    else
    {
        swap(&newProc, &proc[myqueue.front()]);
        swapArr[myqueue.front()] = copy1Struct(newProc);
        myqueue.push(myqueue.front());
        myqueue.pop();
    }
}

void RandomSwap(process* proc, process newProc, int* randArr, int swapCount, process* swapArr)
{
	proc[randArr[swapCount]].swap = 1;
	swap(&proc[randArr[swapCount]], &newProc);
	swapArr[swapCount]= copy1Struct(newProc);
	swapCount++;
}

void FIFO(process proc[], process newProc, process* swapArr)
{
    if(myqueue.empty())
    {
        for(int i = 0;i<20;i++)
        {
            myqueue.push(i);
        }
    }
    else
    {
        if(newProc.id != proc[myqueue.front()].id && newProc.page != proc[myqueue.front()].page)
        {
            swap(&newProc, &proc[myqueue.front()]);
            swapArr[myqueue.front()] = copy1Struct(newProc);
            myqueue.push(myqueue.front());
            myqueue.pop();
        }
        
    }
}


#endif
