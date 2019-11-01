#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <queue>
#include <map>
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

bool compareByArrival(Process p, Process q)
{
    return p.getArrivalTime() < q.getArrivalTime();
}

bool compareById(Process p, Process q)
{
    return p.getId() < q.getId();
}

void display(Process P[], int jobCount, float avgwt = 0, float avgtat = 0)
{
	sort(P,P+jobCount,compareById);
	cout<<"\n\n\t\t The Process Status \n\n";
	cout<<"\tProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurn Around Time\tWaiting Time";
	for (int i = 0; i < jobCount; ++i)
		cout<<"\n\t\t"<<P[i].getId()<<"\t\t"<<P[i].getArrivalTime()<<"\t\t"<<P[i].getBurstTime()<<"\t\t"
		<<P[i].getCompletionTime()<<"\t\t"<<P[i].getTurnAroundTime()<<"\t\t"<<P[i].getWaitingTime();
	cout<<"\n\n\t\tAverage Waiting Time: "<<avgwt;
	cout<<"\n\t\tAverage Turn Around Time: "<<avgtat;
	cout<<"\n\n\n";

}

void getData(Process P[], int &jobCount)
{
	cout<<"\n\n\t\t Process Data: ";
	cout<<"\t How many Process?";
	cin>>jobCount;
	int x;
	for(int i=0; i<jobCount; i++)
	{
		P[i].setId(i+1);
		cout<<"\n\t Process ID: ";
		cout<<P[i].getId();
		cout<<"\n\t Enter the Process Arrival Time: ";
		cin>>x;
		P[i].setArrivalTime(x);
		cout<<"\n\t Enter the Process Burst Time: ";
		cin>>x;
		P[i].setBurstTime(x);
	}
}

void generateRandomData(Process P[], int jobCount)
{
	srand(time(NULL));
	for(int i=0; i<jobCount; i++)
	{
		P[i].setId(i+1);
		P[i].setArrivalTime(rand()%(16));
		P[i].setBurstTime(rand()%20+2);
		P[i].setCompletionTime(0);
		P[i].setTurnAroundTime(0);
		P[i].setWaitingTime(0);
	}

}


void RoundRobin(Process P[], int jobCount)
{
    cout<<"\n*** Round Robin ***\n";

    int tQuantum = 2,t;
    queue<Process> proc;
    bool inQueue[jobCount+1];
    int c=0;
    for(int i = 0;i<jobCount+1;i++){
    	inQueue[i]=false;
    }
    for (t = 0;  ; t++) {
    	for (int i = 0; i < jobCount; ++i)
    	{
    		if(P[i].getArrivalTime()==t){
    			proc.push(P[i]);c++;
    		
    			inQueue[P[i].getId()]=true;
    		}
    	}
    	if(!proc.empty()) break;
    }
   // cout<<proc.front().getId()<<"\n";
    map<int, int> id_compl;
    int k=0;
    	while(!proc.empty()){
    		Process p = proc.front();
    		proc.pop();
    		int tq=min(tQuantum, p.getBurstTime());
    		cout<<p.getId()<<"("<<tq<<"-"<< t+tq<<")-";
    		int b=p.getBurstTime();
    		p.setBurstTime(p.getBurstTime()-tq);
    		t+=tq;
    		for (int j = 0; j < jobCount; ++j)
    		{
    			if(!inQueue[P[j].getId()] && P[j].getArrivalTime()<=t){
    				proc.push(P[j]);c++;
    				inQueue[P[j].getId()]=true;
    			}
    		}

    		if(p.getBurstTime()==0) {
    			p.setCompletionTime(t);
    			id_compl[p.getId()]=p.getCompletionTime();
    		} else {
    			proc.push(p);
    		}

    		
    	}
    	float avgWaitTime=0, avgTurnAroundTime=0;
    	for (int i = 0; i < jobCount; ++i)
    	{
    		P[i].setCompletionTime(id_compl[P[i].getId()]);
    		P[i].setTurnAroundTime(P[i].getCompletionTime() - P[i].getArrivalTime());
		P[i].setWaitingTime(P[i].getTurnAroundTime() - P[i].getBurstTime());
    	avgWaitTime+=P[i].getWaitingTime();
		avgTurnAroundTime+=P[i].getTurnAroundTime();
    	}
    avgWaitTime = (float)avgWaitTime/jobCount;
	avgTurnAroundTime = (float)avgTurnAroundTime/jobCount;
    
    display(P,jobCount,avgWaitTime,avgTurnAroundTime);

}

void FirstComeFirstServed(Process P[], int jobCount)
{
    
    cout<<"\n*** FCFS ***\n";

    float avgWaitTime=0, avgTurnAroundTime=0;

    sort(P, P+jobCount, compareByArrival); // Sorting the processes according to Arrival Time
	
	for(int i = 0, prevEnd =0 ;i < jobCount; i++){
		P[i].setCompletionTime(max(prevEnd, P[i].getArrivalTime()) + P[i].getBurstTime());
		P[i].setTurnAroundTime(P[i].getCompletionTime() - P[i].getArrivalTime());
		P[i].setWaitingTime(P[i].getTurnAroundTime() - P[i].getBurstTime());
		prevEnd = P[i].getCompletionTime();
		
		avgWaitTime+=P[i].getWaitingTime();
		avgTurnAroundTime+=P[i].getTurnAroundTime();
	}
	
	avgWaitTime = (float)avgWaitTime/jobCount;
	avgTurnAroundTime = (float)avgTurnAroundTime/jobCount;
    
    display(P,jobCount,avgWaitTime,avgTurnAroundTime);
}

void ShortestJobFirst(Process P[], int jobCount) // Shortest job first non preemptive
{
	cout<<"\n*** SJF ***\n";
	int executedCount = 0, time = 0;
	float avgWaitTime = 0, avgTurnAroundTime = 0;
	sort(P, P+jobCount+1, compareByArrival);
	bool processActive[jobCount] = {false};
	Process processMinBurstTime;
	vector <Process> processInQueue;

	for(time = 0; executedCount<jobCount;)
	{
		for(int i=0; i<jobCount; i++)
		{
			if(!processActive[P[i].getId()-1] && P[i].getArrivalTime()<=time)		//To check if process is executed before and also whether it has arrived or not
			{
				processInQueue.push_back(P[i]);				// Pushed to Process Arrived Vector
				processActive[P[i].getId()-1] = true;
			}

			if(processInQueue.size()!=0)
			{
				Process processMinBurstTime = *min_element(processInQueue.begin(),
					processInQueue.end(), compareByBurst);

			// Process Execution

				time += processMinBurstTime.getBurstTime();
				processMinBurstTime.setCompletionTime(time);
				processMinBurstTime.setTurnAroundTime(time - processMinBurstTime.getArrivalTime());
				processMinBurstTime.setWaitingTime(processMinBurstTime.getTurnAroundTime()
	 		- processMinBurstTime.getBurstTime());

				executedCount++;

				processInQueue.erase(min_element(processInQueue.begin(),
					processInQueue.end(), compareByBurst));

				int q=0;
				while(processMinBurstTime.getId()!=P[q].getId())
					q++;
				P[q] = processMinBurstTime;


			avgWaitTime+=P[q].getWaitingTime();
			avgTurnAroundTime+=P[q].getTurnAroundTime();
			}

			else
				time++;

		}

	}

	avgWaitTime /= jobCount;
	avgTurnAroundTime /= jobCount;

	display(P,jobCount,avgWaitTime,avgTurnAroundTime);
}


int main()
{
	int choice = 0, jobCount;
	cout<<"*****Menu*****\n";
	cout<<" 1. FCFS\n 2. SJF\n 3. Round Robin\n 0. Exit\n";
	cout<<"Enter your choice [0-3] : ";
	cin>>choice;
	cout<<"No. of processes : ";
	cin>>jobCount;
	Process P[jobCount];
	generateRandomData(P, jobCount);
	switch(choice) {
		case 1 : {
			FirstComeFirstServed(P, jobCount);
			break;
		}
		case 2 : {
			// SJF
			break;
		}
		case 3 : {
			RoundRobin(P, jobCount);
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
