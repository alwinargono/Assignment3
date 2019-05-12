#ifndef PAGING_H
#define PAGING_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>


using namespace std;

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

    queue<int>myqueue;

//    int arrival;
//    int duration;
//    int startTime;
//    int endTime;
//    int tempDur;
//    int remaining;
//    bool running;
//    bool done;

    process(): id(-1),page(0), swap(0), killed(0), pageAllocated(0), modified(0),
    		terminated(0), created(0)
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

// A function to implement bubble sort and modify the array
void SortArvlLtoH(process arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)
    {
        // Last i elements are already in place
        for (j = 0; j < n-i-1; j++)
        {
//            if (arr[j].arrival > arr[j+1].arrival)
            {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
    return;
}

void FIFO(process proc[], int processIndexSwap, int swap)
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
        swap(proc[page],proc[myqueue.top]);
        myqueue.push(myqueue.front());
        myqueue.pop();
    }
}

#endif
