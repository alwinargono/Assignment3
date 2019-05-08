#include "paging.h"
#include <iostream>

using namespace std;

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

int main()
{
	int jobCount = 0;
	process procArray[100];
	string buffer;
	process physPage[20];
	process virPage[100];
	process *swap;
	process created[100];
	int createdCount = 0;
	int swapCount = 0;
	int physPageCount = 0;
	int virPageCount = 0;

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

        	}
        	else if(procArray[i].action == 'F' || procArray[i].action == 'f')
        	{
        		bool found = 0;
        		for(int j = 0; j<createdCount; j++)
        		{
        			if(created[j].id == procArray[i].id)
        			{
        				found = 1;
        				//        		        				created[j].terminated = 1;
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
        				if(count == procArray[i].page)
        				{
        					found = 1;
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

	return 0;
}
