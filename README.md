# CPU Scheduling Algorithms

<img src="https://img.shields.io/badge/Operating Systems-CPU Scheduling Algorithm-<green>"> <img src="https://img.shields.io/static/v1?label=Language&message=CPP&color=blue">
<br>

Co-creator: [@leonatwork](https://github.com/leonatwork)  <br>
Dated: 01st November 2019 <br>
<br>
Implemented following CPU scheduling algorithms in C++ with arrival time <br>
<br>
* First Come First Served<br>
* Shortest Job First<br>
* Round Robin<br>
* Shortest Job Remaining First<br>
<br>
Some of the features included are, <br>
- Concept of Arrival Time <br>
- Random generation of Process data <br>
- Tabular representation of individual process data like, Turn Around Time, Waiting Time etc. <br>
- Calculation of Average Turn Around Time and Waiting Time <br>
<br>

## First Come First Served <br>

As the name suggests, the process which arrives first, will be served first.This scheduling algorithm is <b> non- preemptive </b>. Here, processes are sorted by their respective arrival time and then are executed. The process with lowest arrival time will get priority in execution.<br>
<br>

## Shortest Job First <br>

Processes have their respective burst time, which suggests how much CPU time a process requires in order to get executed. This scheduling algorithm in <b> Non- Preemptive </b>. Here, the processes are first sorted with their respective arrival time. As soon the process arrives, it gets enqueued in a queue of arrived processes. The processes are executed in ascending order of their burst time in from the queue of arrived process. <br>
<br>

## Round Robin <br>

Here, the process starvation is least as every process is executed in round robin fashion for a certain specified time quantum. Once a process is executed for the given time quantum, it leaves the CPU and gives turn to next process. This process is <b> Preemptive </b>.
<br>

## Shortest Job Remaining First <br>

It is the <b> preemptive </b> implementation of the algorithm Shortest job first. As soon as, a job arrives having lesser burst time than the current executing process, CPU preempts the current executing process and fetchs the one with the least burst time.

## Working Snapshots <br>
<br>
<img src="working snaps/img1.JPG">
<br>
<img src="working snaps/img2.JPG">
<br>
<img src="working snaps/img3.JPG">
<br>
