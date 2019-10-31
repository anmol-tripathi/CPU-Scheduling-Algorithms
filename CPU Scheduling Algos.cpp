#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <time.h>
using namespace std;

class Process {
	int id;
	int burstTime;
	int arrivalTime;
	int completionTime;
	int turnAroundTime;
	int waitingTime;
public :
	int getId() {
		return id;
	}
	int getBurstTime() {
		return burstTime;
	}
	int getArrivalTime() {
		return arrivalTime;
	}
	int getCompletionTime() {
		return completionTime;
	}
	int getTurnAroundTime() {
		return turnAroundTime;
	}
	int getWaitingTime() {
		return waitingTime;
	}
	void setId(int id) {
		this->id = id;
	}
	void setBurstTime(int burstTime) {
		this->burstTime = burstTime;
	}
	void setArrivalTime(int arrivalTime) {
		this->arrivalTime = arrivalTime;
	}
	void setCompletionTime(int completionTime) {
		this->completionTime = completionTime;
	}
	void setTurnAroundTime(int turnAroundTime) {
		this->turnAroundTime = turnAroundTime;
	}
	void setWaitingTime(int waitingTime) {
		this->waitingTime = waitingTime;
	}
};

// bool compareByArrival(Process p, Process q)
// {
//     return p.arrivalTime < q.arrivalTime;
// }

void display(Process P[], int jobCount, float avgwt = 0, float avgtat = 0)
{
	cout<<"\n\n\t\t The Process Status \n\n";
	cout<<"\tProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time";
	for (int i = 0; i < jobCount; ++i)
		cout<<"\n\t\t"<<P[i].getId()<<"\t\t"<<P[i].getArrivalTime()<<"\t\t"<<P[i].getBurstTime()<<"\t\t"
		<<P[i].getCompletionTime()<<"\t\t"<<P[i].getTurnAroundTime()<<"\t\t"<<P[i].getWaitingTime();
	cout<<"\n\n\t\tAverage Waiting Time: "<<avgwt;
	cout<<"\n\t\tAverage Turn Around Time: "<<avgtat;
	cout<<"\n\n\n";

}

// void getData(struct Process P[], int &jobCount)
// {
// 	cout<<"\n\n\t\t Process Data: ";
// 	cout<<"\t How many Process?";
// 	cin>>jobCount;
// 	for(int i=0; i<jobCount; i++)
// 	{
// 		cout<<"\n Process "<<i;
// 		cout<<"\n\t Enter the Process ID: ";
// 		cin>>P[i].id;
// 		cout<<"\n\t Enter the Process Arrival Time: ";
// 		cin>>P[i].arrivalTime;
// 		cout<<"\n\t Enter the Process Burst Time: ";
// 		cin>>P[i].burstTime;
// 	}
// }


void generateRandomData(Process P[], int jobCount)
{
	srand(time(NULL));
	cout<<"\n\n Generating Random Data";
	for(int i=0; i<jobCount; i++)
	{
		P[i].setId(i+1);
		P[i].setArrivalTime(rand()%(16));
		P[i].setBurstTime(rand()%20+2);
		P[i].setCompletionTime(0);
		P[i].setTurnAroundTime(0);
		P[i].setWaitingTime(0);
	}
	cout<<"\n\n Displaying Data";
	display(P,jobCount);

}


// float RoundRobin(struct Process P[])
// {
//     int TimeQuantum = 3; // Allocated Time Quantum
//     int time = 0;
// 	float avgwt = 0;
// 	float avgtat = 0;
	
// 	avgwt /= jobCount;
// 	avgtat /= jobCount;
// 	display(P,jobCount,avgwt,avgtat);
//     return 0;

// }

// float FirstComeFirstServed(struct Process P[])
// {
//     sort(P, P+jobCount+1, compareByArrival); // Sorting the processes according to Arrival Time
// 	int time = 0;
// 	float avgwt = 0;
// 	float avgtat = 0;
//     for(int i=0; i<jobCount; i++)
//     {
//         if(time>=P[i].arrivalTime)
//         {
//         	time += P[i].burstTime;
//         	P[i].completionTime = time;
//         	P[i].turnAroundTime = time - P[i].arrivalTime;
//         	P[i].waitingTime = P[i].turnAroundTime - P[i].burstTime;
//         }

//         else
//         {
//         	time+=1;
//         	i--;
//         }
//         avgtat += P[i].turnAroundTime;
//     	avgwt += P[i].waitingTime;
//     }
//     avgwt = (float)(avgwt/jobCount);
//     avgtat = (float)(avgtat/jobCount);
//     display(P,jobCount,avgwt,avgtat);
//     return 0;
// }

// float ShortestJobFirst(struct Process P[]) // Shortest job first non preemptive
// {
// 	int time = 0;
// 	int turnAroundTime[jobCount];
// 	int waitingTime[jobCount];
// 	float avgwt = 0;
// 	float avgtat = 0;
// 	queue<Process> readyJobs;
// 	sort(P, P+jobCount+1, compareByArrival);
// 	while(time>=P[i].arrivalTime)
// 	{
// 		readyJobs.push(P[i]);
// 		i++;
// 	}

// 	else
// 	{
// 		time+=1;
// 	}
// 	avgwt /= jobCount;
// 	avgtat /= jobCount;
// 	display(P,jobCount,avgwt,avgtat);
//     return 0;
// }


int main()
{
	int choice = 0, jobCount;
	cout<<"*****Menu*****\n";
	cout<<" 1. FCFS\n 2. SJF\n 3. Round Robin\n 4. Generate data \n 0. Exit\n";
	cout<<"Enter your choice [0-4] : ";
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
		case 4 : {
			cout<<"No. of processes :";
			cin>>jobCount;
			Process P[jobCount];
			generateRandomData(P,jobCount);
			break;
		}
		case 0: {
			exit(1);
			break;
		}
	}
	return 0;
	// int ch=1; // To select between average waiting time or average turnaround time
 //    struct Process P[jobCount];
 //    generateRandomData(P,jobCount);
 //    FirstComeFirstServed(P);
 //    ShortestJobFirst(P);
}
