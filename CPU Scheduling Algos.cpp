#include <iostream>
#include <algorithm>
using namespace std;

int jobCount=4;

struct Process {

int id;
int burstTime;
int arrivalTime;
int completionTime;
float turnAroundTime;
float waitingTime;

};

bool compareByArrival(Process p, Process q)
{
    return p.arrivalTime < q.arrivalTime;
}

void display(struct Process P[], int jobCount, float avgwt = 0, float avgtat = 0)
{
	cout<<"\n\n\t\t The Process Status \n\n";
	cout<<"\tProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time";
	for (int i = 0; i < jobCount; ++i)
		cout<<"\n\t\t"<<P[i].id<<"\t\t"<<P[i].arrivalTime<<"\t\t"<<P[i].burstTime<<"\t\t"<<P[i].completionTime<<"\t\t"<<P[i].turnAroundTime<<"\t\t"<<P[i].waitingTime;
	cout<<"\n\n\t\tAverage Waiting Time: "<<avgwt;
	cout<<"\n\t\tAverage Turn Around Time: "<<avgtat;
	cout<<"\n\n\n";

}

void getData(struct Process P[], int &jobCount)
{
	cout<<"\n\n\t\t Process Data: ";
	cout<<"\t How many Process?";
	cin>>jobCount;
	for(int i=0; i<jobCount; i++)
	{
		cout<<"\n Process "<<i;
		cout<<"\n\t Enter the Process ID: ";
		cin>>P[i].id;
		cout<<"\n\t Enter the Process Arrival Time: ";
		cin>>P[i].arrivalTime;
		cout<<"\n\t Enter the Process Burst Time: ";
		cin>>P[i].burstTime;
	}
}


void generateRandomData(struct Process P[], int jobCount)
{
	srand(time(NULL));
	cout<<"\n\n Generating Random Data";
	for(int i=0; i<jobCount; i++)
	{
		P[i].id = rand()%(2001)+1000;
		P[i].arrivalTime = rand()%(16);
		P[i].burstTime = rand()%20+2;
	}
	cout<<"\n\n Displaying Data";
	display(P,jobCount);

}


float RoundRobin(struct Process P[])
{
    int TimeQuantum = 3; // Allocated Time Quantum
    int time = 0;
	float avgwt = 0;
	float avgtat = 0;
	
	avgwt /= jobCount;
	avgtat /= jobCount;
	display(P,jobCount,avgwt,avgtat);
    return 0;

}

float FirstComeFirstServed(struct Process P[])
{
    sort(P, P+jobCount+1, compareByArrival); // Sorting the processes according to Arrival Time
	int time = 0;
	float avgwt = 0;
	float avgtat = 0;
    for(int i=0; i<jobCount; i++)
    {
        if(time>=P[i].arrivalTime)
        {
        	time += P[i].burstTime;
        	P[i].completionTime = time;
        	P[i].turnAroundTime = time - P[i].arrivalTime;
        	P[i].waitingTime = P[i].turnAroundTime - P[i].burstTime;
        }

        else
        {
        	time+=1;
        	i--;
        }
        avgtat += P[i].turnAroundTime;
    	avgwt += P[i].waitingTime;
    }
    avgwt = (float)(avgwt/jobCount);
    avgtat = (float)(avgtat/jobCount);
    display(P,jobCount,avgwt,avgtat);
    return 0;
}

float ShortestJobFirst(struct Process P[]) // Shortest job first non preemptive
{
	int time = 0;
	int turnAroundTime[jobCount];
	int waitingTime[jobCount];
	float avgwt = 0;
	float avgtat = 0;
	queue<Process> readyJobs;
	sort(P, P+jobCount+1, compareByArrival);
	while(time>=P[i].arrivalTime)
	{
		readyJobs.push(P[i]);
		i++;
	}

	else
	{
		time+=1;
	}
	avgwt /= jobCount;
	avgtat /= jobCount;
	display(P,jobCount,avgwt,avgtat);
    return 0;
}


int main()
{
	int choice = 0;
	cout<<"*****Menu*****\n";
	cout<<" 1. FCFS\n 2. SJF\n 3. Round Robin\nEnter your choice [1-3] : ";
	cin>>choice;
	switch(choice) {
		case 1 : {
			// FCFS
			break;
		}
		case 2 : {
			// SJF
			break;
		}
		case 3 : {
			// Round Robin
			break;
		}
	}

	int ch=1; // To select between average waiting time or average turnaround time
    struct Process P[jobCount];
    generateRandomData(P,jobCount);
    FirstComeFirstServed(P);
    ShortestJobFirst(P);
}