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

bool compareByBurst(Process p, Process q)
{
    return p.getBurstTime() < q.getBurstTime();
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
	cout<<"\n\t*** Round Robin ***\n";
    int tQuantum;
    cout<<"\t Time quantum : ";
    cin>>tQuantum;
    bool inQueue[jobCount+1];
  	fill(inQueue, inQueue+jobCount+1, false);
    map<int, int> id_compl;
	int jobDone = 0,curTime=0;
	queue<Process> ready_queue;
	do {
		for (int i = 0; i < jobCount; ++i) {
			if(!inQueue[P[i].getId()] && P[i].getArrivalTime()==curTime) {
				ready_queue.push(P[i]);
				inQueue[P[i].getId()]=true;
			}
		}
		if(!ready_queue.empty()) {
    		Process p = ready_queue.front();
    		ready_queue.pop();
    		int tq=min(tQuantum, p.getBurstTime());
    		// cout<<"p"<<p.getId()<<"->";
    		int b=p.getBurstTime();
    		p.setBurstTime(p.getBurstTime()-tq);
    		for (int i = curTime+1; i <= curTime+tq; ++i)
    		{
    			for (int j = 0; j < jobCount; ++j)
    			{
    				if(!inQueue[P[j].getId()] && P[j].getArrivalTime()==i) {
					ready_queue.push(P[j]);
					inQueue[P[j].getId()]=true;
					}
    			}
    		}
    		curTime += tq;
    		if(p.getBurstTime()==0) {
    			jobDone++;
    			p.setCompletionTime(curTime);
    			id_compl[p.getId()]=p.getCompletionTime();
    		} else {
    			ready_queue.push(p);
    		}
		} else {
			curTime++;
		}
	} while(jobDone!=jobCount);

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

    cout<<"\n\t*** FCFS ***\n";

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
	cout<<"\n\t*** SJF ***\n";

	int executedCount = 0;
	bool processActive[jobCount];
	fill(processActive, processActive+jobCount, false);
	vector <Process> processInQueue;
	map<int, int> id_compl;
	for(int time = 0; executedCount<jobCount;) {
		for(int i=0; i<jobCount; i++) {
			if(!processActive[P[i].getId()-1] && P[i].getArrivalTime()<=time){ 		//To check if process is executed before and also whether it has arrived or not
				processInQueue.push_back(P[i]);				// Pushed to Process Arrived Vector
				processActive[P[i].getId()-1] = true;
			}
		}
		if(processInQueue.size()!=0) {
			vector<Process>::iterator minPosition = min_element(processInQueue.begin(),
			processInQueue.end(), compareByBurst);
			Process processMinBurstTime = *minPosition;
			time += processMinBurstTime.getBurstTime();
			id_compl[processMinBurstTime.getId()] = time;
			executedCount++;
			processInQueue.erase(minPosition);

		} else {
			time++;
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

void ShortestJobRemainingFirst(Process P[], int jobCount)
{
	cout<<"\n\t*** SJRF ***\n";
	int time = 0, executedCount = 0;
	float avgTurnAroundTime = 0, avgWaitTime = 0;
	vector <Process> processInQueue;
	bool inQueue[jobCount];
	fill(inQueue, inQueue+jobCount, false);
	map<int,int> pid_compl;
	while(executedCount!=jobCount)
	{
		for(int i=0; i<jobCount; i++)
		{
			if((P[i].getArrivalTime()<=time)&&(inQueue[i]==false))
			{
				processInQueue.push_back(P[i]);
				inQueue[i]=true;
			}

		}

		if(processInQueue.size()!=0)
		{
			vector<Process>::iterator minPosition = min_element(processInQueue.begin(),
				processInQueue.end(), compareByBurst);
			(*minPosition).setBurstTime((*minPosition).getBurstTime()-1);
			time++;
			if((*minPosition).getBurstTime()==0)
			{
				pid_compl[(*minPosition).getId()]=time;
				executedCount++;
				processInQueue.erase(minPosition);
			}

		}
		else {
			time++;
		}
	}
	for(int i=0; i<jobCount ; i++){
		P[i].setCompletionTime(pid_compl[P[i].getId()]);
		P[i].setTurnAroundTime(P[i].getCompletionTime() - P[i].getArrivalTime());
		P[i].setWaitingTime(P[i].getTurnAroundTime() - P[i].getBurstTime());
		avgWaitTime+=P[i].getWaitingTime();
		avgTurnAroundTime+=P[i].getTurnAroundTime();
	}
	avgWaitTime = (float)avgWaitTime/jobCount;
	avgTurnAroundTime = (float)avgTurnAroundTime/jobCount;

 	display(P,jobCount,avgWaitTime,avgTurnAroundTime);

}

int main()
{
	int schedulingType, dataInputChoice, jobCount;
	while(1) {

		cout<<"\n\t*****CPU Scheduling Algorithms*****\n";

		cout<<"\t 1. First Come First Served (FCFS)\n\t 2. Shortest Job First (SJF)\n\t 3. Round Robin (RR)\n\t 4. Shortest Job Remaining First (SJRF)\n\t 5. All\n\t 0. Exit\n";
		cout<<"\n\t Enter your choice [0-5] : ";

		cin>>schedulingType;

		if(schedulingType == 0) {
			exit(1);
		}

		cout<<"\n\t Manually enter data or Auto generated data? \n\t 1. Manually \t 2. Random Generated \n";
		cout<<"\n\t Enter your choice [1/2] : ";

		cin>>dataInputChoice;

		cout<<"\t No. of processes : ";
		cin>>jobCount;

		Process P[jobCount];

		switch(dataInputChoice){
			case 1: {
				getData(P,jobCount);
				break;
			}

			case 2: {
				generateRandomData(P, jobCount);
			}
		}

		switch(schedulingType) {
			case 1 : {
				FirstComeFirstServed(P, jobCount);
				break;
			}
			case 2 : {
				ShortestJobFirst(P, jobCount);
				break;
			}
			case 3 : {
				RoundRobin(P, jobCount);
				break;
			}
			case 4 : {
				ShortestJobRemainingFirst(P, jobCount);
				break;
			}
			case 5 : {
                FirstComeFirstServed(P, jobCount);
                ShortestJobFirst(P, jobCount);
                RoundRobin(P, jobCount);
                ShortestJobRemainingFirst(P, jobCount);
				break;
			}
		}
	}
	return 0;
}
