#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char id;
    int arrival, burst, start, finish, waiting, turnaround;
} Process;

int compare(const void *a, const void *b)
{
    return ((Process *)a)->arrival - ((Process *)b)->arrival;
}

void calculateFCFS(Process *processes, int n)
{
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    qsort(processes, n, sizeof(Process), compare);

    for (int i = 0; i < n; ++i)
    {
        processes[i].start = (i == 0) ? processes[i].arrival : (processes[i - 1].finish > processes[i].arrival ? processes[i - 1].finish : processes[i].arrival);
        processes[i].finish = processes[i].start + processes[i].burst;
        processes[i].waiting = processes[i].start - processes[i].arrival;
        processes[i].turnaround = processes[i].finish - processes[i].arrival;
        totalWaitingTime += processes[i].waiting;
        totalTurnaroundTime += processes[i].turnaround;
    }

    printf("\nProcess Information:\n---------------------------------------------------------------\n");
    printf("%-10s|%-15s|%-15s|%-20s|\n", "Process", "A.T", "W.T", "T.A.T");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; ++i)
        printf("%-10c|%-15d|%-15d|%-20d|\n", processes[i].id, processes[i].arrival, processes[i].waiting, processes[i].turnaround);
    printf("---------------------------------------------------------------\n");
    printf("\nAverage Waiting Time: %.2f\nAverage Turnaround Time: %.2f\n", (float)totalWaitingTime / n, (float)totalTurnaroundTime / n);

    printf("\nGantt Chart:\n+");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < processes[i].burst * 2; ++j)
            printf("-");
    printf("+\n|");
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < processes[i].burst - 1; ++j)
            printf(" ");
        printf(" %c", processes[i].id);
        for (int j = 0; j < processes[i].burst - 1; ++j)
            printf(" ");
        printf("|");
    }
    printf("\n+");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < processes[i].burst * 2; ++j)
            printf("-");
    printf("+\n");

    int currentTime = 0;
    printf("%d", currentTime);
    for (int i = 0; i < n; ++i)
    {
        int gap = (processes[i].burst * 2) - (processes[i].finish > 9 ? 2 : 1);
        for (int j = 0; j < gap / 2 + 1; ++j)
            printf(" ");
        printf("%d", processes[i].finish);
        for (int j = 0; j < gap - gap / 2; ++j)
            printf(" ");
    }
    printf("\n");
}

int main()
{
    int numProcesses;
    printf("\t*****NISHAN DHAKAL*****\n******FCFS Scheduling Algorithm******\n\nEnter the number of processes: ");
    scanf("%d", &numProcesses);
    Process *processes = (Process *)malloc(numProcesses * sizeof(Process));
    printf("Enter the process ID (character), arrival time, and burst time for each process:\n");
    for (int i = 0; i < numProcesses; ++i)
    {
        printf("For Process %d: ", i + 1);
        scanf(" %c %d %d", &processes[i].id, &processes[i].arrival, &processes[i].burst);
    }
    calculateFCFS(processes, numProcesses);
    free(processes);
    return 0;
}
