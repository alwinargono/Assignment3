#include "paging.h"
#include <cstdlib>
#include <ctime>

static void getRand (int *dst) { //generate random num 1-20
    int sz, pos, i, src[20];
    for (i = 0; i < sizeof(src)/sizeof(*src); i++)
        src[i] = i + 1;
    sz = 20;
    for (i = 0; i < 20; i++) {
        pos = rand() % sz;
        dst[i] = src[pos];
        src[pos] = src[sz-1];
        sz--;
    }
}

bool checkSameProcess(process* proc, int ID, int count)
{
	for(int i = 0; i< count; i++)
	{
		if(proc[i].id == ID)
			return true;
	}
	return false;
}

void resetProcessVal(process proc)
{
	proc.id = -1;
	proc.page=0;
	proc.swap=0;
	proc.killed=0;
	proc.pageAllocated=0;
	proc.modified=0;
	proc.terminated=0;
	proc.created=0;
	proc.pageNum=0;
	return;
}

void printCreatedProc(process* proc)
{
	int count = 0;
	
	for(int i = 0;i<20;i++)
	{
		if(proc[i].id != -1)
		{
			cout << "Process id: " << proc[i].id << endl;
			cout << "Virtual address: " << proc[i].vir << endl;
			cout << "Physical address: " << proc[i].phys << endl;
			cout << "------------------" <<endl;

		}
	}
}

void printPhys(process* proc)
{
	for(int i = 0; i<20; i++)
	{
		cout << "index " << i << "\t\t";
		if(proc[i].id == -1)
			cout << "FREE\n";
		else
			cout << "Process id: " << proc[i].id << endl;

	}
}

bool checkCreated(process* arr, int id)
{
	for(int i = 0; i<sizeof(arr); i++)
	{
		if(arr[i].id == id)
			return true;
	}
	return false;
}

bool checkAllMod(process* arr)
{
	for(int i = 0; i<sizeof(arr); i++)
	{
		if(arr[i].modified == false)
			return false;
	}
	return true;
}

int main()
{
	int jobCount = 0;
	process procArray[100];
	string buffer;
	process physPage[20];
//	process virPage[100];
	process swapArr[100];
	process created[100];
	int createdCount = 0;
	int swapCount = 0;
	int physPageCount = 0;
//	int virPageCount = 0;
	int choice;
	int randomNum[20];
	int index;

	srand (time (NULL));
	getRand(randomNum);
	for(int i = 0; i< 20;i++)
	{
		cout << randomNum[i] << endl;
	}
    ifstream fin("memory.dat");
    if (!fin.good())
    {
    	cout << "File not found\n";
	}
    else
    {
        cout << "File is found\n";
        while (!fin.eof() && jobCount < 100)
	    {
            getline(fin, buffer);
            cout << buffer << endl;
	        stringstream ss(buffer);
	        ss >> procArray[jobCount].id >> procArray[jobCount].action >> procArray[jobCount].page;
            jobCount++;
	    }
	    fin.close();
        cout << "Job Count : " << jobCount << endl;
        cout << "algorithm: 1 Fifo 2 Lru 3 Random\n";
        cin >> choice;
        //printStruct(procArray, 0, jobCount);

        for(int i = 0; i < jobCount; i++)
        {
        	if(procArray[i].action == 'C' || procArray[i].action == 'c')
        	{
        		if(checkSameProcess(created, procArray[i].id, createdCount)) //process already created
        		{
        			//terminate and free all its pages before recreated
        			for(int j = 0; j<createdCount; j++)
        			{
        			     if(created[j].id == procArray[i].id)
        			     {
//        			        created[j].terminated = 1;
        			        //find and free all pages
        			        int count = 0;
        			        while(count<created[j].pageAllocated)
        			        {
        			        	int k = 0;
        			        	if(physPage[k].id==procArray[i].id)
        			        	{
        			        		resetProcessVal(physPage[k]);
        			        		count++;
        			        	}
        			        }
        			        created[j].pageAllocated = 0;
        			     }
        			}
        			cout << "Freed before re-created\n";
        		}
        		else
        		{
        			//create process
        			created[createdCount]=copy1Struct(procArray[i]);
        			created[createdCount].created = 1;
        			createdCount++;
        			cout << "Process created\n";
        			printStructInfo(created, 0, createdCount);
        		}
        	}
        	else if(procArray[i].action == 'T' || procArray[i].action == 't')
        	{
        		bool found = 0;
        		for(int j = 0; j<createdCount; j++)
        		{
        			if(created[j].id == procArray[i].id)
        			{
        				found = 1;
        				created[j].terminated = 1;
        				//find and free all pages
        				int count = 0;
        				while(count<created[j].pageAllocated)
        				{
        					int k = 0;
        					if(physPage[k].id==procArray[i].id)
        					{
        						resetProcessVal(physPage[k]);
        						count++;
        					}
        				}
        				created[j].pageAllocated = 0;
        				cout << "Freed before re-created\n";
        			}
        		}
        		if(!found)
        		{
        			created[createdCount]=copy1Struct(procArray[i]);
        			created[createdCount].killed = 1;
        			createdCount++;
        			cout << "process not found and killed\n";
        			printStructInfo(created, 0, createdCount);
        		}
        	}
        	else if(procArray[i].action == 'A' || procArray[i].action == 'a')
        	{
        		bool valid = checkCreated(created, procArray[i].id);
        		bool allModified = checkAllMod(physPage);
        		if(valid && !allModified)
        		{
        			if(physPageCount < 20)
        			{
        				procArray[i].vir = procArray[i].page;
        				procArray[i].phys = physPageCount;
        				procArray[i].pageAllocated++;
        				physPage[physPageCount] = copy1Struct(procArray[i]);
						cout<< physPage[physPageCount].vir<<" hahahahhahah\n";
        				physPageCount++;
						cout <<"hello "<<procArray[i].vir<<"\n";
        				cout << "adding to physical page\n";
        			}
        			else //flush nonmodified page
        			{

        				for(int y = 0; y<20; y++)
        				{
        					if(!physPage[y].modified)
        					{
        						index= y;
        						break;
        					}
        				}
        				swap(&physPage[index], &procArray[i]);
        			}
        		}
        		else if(valid && allModified)
        		{
					procArray[i].vir = procArray[i].page;
					switch(choice)
        			{
        			case 1: // FIFO
        			case 2: LRU(physPage, procArray[i],swapArr);
        			case 3: RandomSwap(physPage, procArray[i], randomNum, swapCount, swapArr);
        				break;// Random
        			}
        		}
        		else
        			cout << "Process id is not created\n";
        	}
        	else if(procArray[i].action == 'F' || procArray[i].action == 'f')
        	{
        		bool found = 0;
        		for(int j = 0; j<createdCount; j++)
        		{
        			if(created[j].id == procArray[i].id)
        			{
        				found = 1;
        				//created[j].terminated = 1;
        				//find and free all pages
        				int count = 0;
        				while(count<created[j].pageAllocated)
        				{
        					int k = 0;
        					if(physPage[k].id==procArray[i].id)
        					{
        						resetProcessVal(physPage[k]);
        						count++;
        					}
        				}
        				created[j].pageAllocated = 0;
        				cout << "Freed before re-created\n";
        			}
        		}
        		if(!found)
        		{
        			created[createdCount]=copy1Struct(procArray[i]);
        			created[createdCount].killed = 1;
        			createdCount++;
        			cout << "process not found and killed\n";
        			printStructInfo(created, 0, createdCount);
        		}
        	}
        	else if(procArray[i].action == 'R' || procArray[i].action == 'r')
        	{
        		bool found = 0;
        		int count= 0;
        		for(int j = 0; j<createdCount; j++)
           		{
        			if(created[j].id == procArray[i].id)
           			{
        				count++;

        				if(count == procArray[i].vir)
        				{
        					found = 1;
        					procArray[i].accessed = 1;
        				}
           			}
           		}
           		if(!found)
           		{
           			created[createdCount]=copy1Struct(procArray[i]);
           			created[createdCount].killed = 1;
        		    createdCount++;
           			cout << "process not found and killed\n";
           			printStructInfo(created, 0, createdCount);
           		}
        	}
        	else if(procArray[i].action == 'W' || procArray[i].action == 'w')
        	{
        		bool found = 0;
        		int count= 0;
          		for(int j = 0; j<createdCount; j++)
          		{
           			if(created[j].id == procArray[i].id)
           			{
           				count++;
           				if(count == procArray[i].page)
        				{
           					found = 1;
           					created[j].modified = 1;
        				}
        			}
          		}
           		if(!found)
           		{
           			created[createdCount]=copy1Struct(procArray[i]);
           			created[createdCount].killed = 1;
           		    createdCount++;
           		    cout << "process not found and killed\n";
          			printStructInfo(created, 0, createdCount);
           		}
        	}
        	else
        	{
        		cout << "Wrong action character\n";
        	}
        }
    }

    cout << "\nCREATED PROCESS\n\n";
    printCreatedProc(physPage);
    cout << endl;

    cout << "SWAP PROCESS\n\n";
    printCreatedProc(swapArr);
    cout << endl;

    cout << "PHYSICAL PAGE\n\n";
    printPhys(physPage);
    cout << endl;

	return 0;
}
