#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_PROCESSES 100

typedef struct
{
    char id;
    int arrival, burst, remaining, start, finish, waiting, turnaround;
} Process;

void calculateRoundRobin(Process processes[], int n, int quantum)
{
    int totalWaitingTime = 0, totalTurnaroundTime = 0, currentTime = 0, completedProcesses = 0;
    int completed[MAX_PROCESSES] = {0};
    int ganttChart[MAX_PROCESSES], ganttTimes[MAX_PROCESSES];
    int ganttSize = 0;

    // Initialize remaining burst times
    for (int i = 0; i < n; i++)
    {
        processes[i].remaining = processes[i].burst;
    }

    while (completedProcesses < n)
    {
        int progressMade = 0;
        for (int i = 0; i < n; i++)
        {
            if (!completed[i] && processes[i].arrival <= currentTime)
            {
                if (processes[i].remaining > 0)
                {
                    progressMade = 1;
                    int timeSlice = (quantum < processes[i].remaining) ? quantum : processes[i].remaining;
                    processes[i].remaining -= timeSlice;
                    currentTime += timeSlice;

                    // Record Gantt chart
                    ganttChart[ganttSize] = processes[i].id;
                    ganttTimes[ganttSize++] = currentTime;

                    if (processes[i].remaining == 0)
                    {
                        processes[i].finish = currentTime;
                        processes[i].turnaround = processes[i].finish - processes[i].arrival;
                        processes[i].waiting = processes[i].turnaround - processes[i].burst;
                        totalWaitingTime += processes[i].waiting;
                        totalTurnaroundTime += processes[i].turnaround;
                        completed[i] = 1;
                        completedProcesses++;
                    }
                    if (processes[i].remaining == processes[i].burst - timeSlice)
                    {
                        processes[i].start = currentTime - timeSlice;
                    }
                }
            }
        }
        if (!progressMade)
            currentTime++;
    }

    // Display Gantt chart
    printf("\nGantt Chart:\n+");
    for (int i = 0; i < ganttSize; i++)
    {
        printf("-----+");
    }
    printf("\n|");
    for (int i = 0; i < ganttSize; i++)
    {
        printf("  %c  |", ganttChart[i]);
    }
    printf("\n+");
    for (int i = 0; i < ganttSize; i++)
    {
        printf("-----+");
    }
    printf("\n0");
    for (int i = 0; i < ganttSize; i++)
    {
        printf("%6d", ganttTimes[i]);
    }
    printf("\n\nProcess Information:\n");
    printf("---------------------------------------------------------------\n");
    printf("%-10s|%-15s|%-15s|%-20s|\n", "Process", "A.T", "W.T", "T.A.T");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%-10c|%-15d|%-15d|%-20d|\n", processes[i].id, processes[i].arrival, processes[i].waiting, processes[i].turnaround);
    }
    printf("---------------------------------------------------------------\n");
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

int main()
{
    int numProcesses, timeQuantum;

    printf("\t*****NISHAN DHAKAL*****\n");
    printf("******Round Robin Scheduling Algorithm******\n\n");
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    Process processes[MAX_PROCESSES];

    printf("\nEnter the process ID (character), arrival time, and burst time for each process (all in one line):\n");
    for (int i = 0; i < numProcesses; i++)
    {
        printf("For Process %d: ", i + 1);
        scanf(" %c %d %d", &processes[i].id, &processes[i].arrival, &processes[i].burst);
    }
    calculateRoundRobin(processes, numProcesses, timeQuantum);
    return 0;
}
