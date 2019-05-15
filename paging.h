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
    		terminated(0), created(0), pageNum(0), modNum(-1)
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

//// A function to implement bubble sort and modify the array
//void SortArvlLtoH(process arr[], int n)
//{
//    int i, j;
//    for (i = 0; i < n-1; i++)
//    {
//        // Last i elements are already in place
//        for (j = 0; j < n-i-1; j++)
//        {
////            if (arr[j].arrival > arr[j+1].arrival)
//            {
//                swap(&arr[j], &arr[j+1]);
//            }
//        }
//    }
//    return;
//}

void LRU(process proc[], process newProc, int processIndexSwap)
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
        myqueue.push(myqueue.front());
        myqueue.pop();
    }
}

void RandomSwap(process* proc, process newProc, int* randArr, int swapCount, process* swapArr)
{
	swap(&proc[randArr[swapCount]], &newProc);
	swapArr[swapCount]= copy1Struct(newProc);
	swapCount++;
}

void FIFO(process proc[], process newProc, int processIndexSwap)
{
    
}

#endif
