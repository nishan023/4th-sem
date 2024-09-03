#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char id;
    int arrival, burst, start, finish, waiting, turnaround;
} Process;
int compareArrival(const void *a, const void *b)
{
    return ((Process *)a)->arrival - ((Process *)b)->arrival;
}
// Calculate SJF (non-preemptive) scheduling
void calculateSJF(Process *processes, int n)
{
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    int completed = 0, currentTime = 0, shortest;
    int *isCompleted = (int *)calloc(n, sizeof(int));
    qsort(processes, n, sizeof(Process), compareArrival);

    while (completed != n)
    {
        shortest = -1;
        for (int i = 0; i < n; ++i)
        {
            if (processes[i].arrival <= currentTime && !isCompleted[i])
            {
                if (shortest == -1 || processes[i].burst < processes[shortest].burst)
                {
                    shortest = i;
                }
            }
        }
        if (shortest == -1)
        {
            currentTime++;
            continue;
        }
        processes[shortest].start = currentTime;
        processes[shortest].finish = processes[shortest].start + processes[shortest].burst;
        processes[shortest].waiting = processes[shortest].start - processes[shortest].arrival;
        processes[shortest].turnaround = processes[shortest].finish - processes[shortest].arrival;
        totalWaitingTime += processes[shortest].waiting;
        totalTurnaroundTime += processes[shortest].turnaround;
        currentTime = processes[shortest].finish;
        isCompleted[shortest] = 1;
        completed++;
    }
    // Display process information and average calculations
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
    int ganttTime = 0;
    printf("%d", ganttTime);
    for (int i = 0; i < n; ++i)
    {
        ganttTime = processes[i].finish;
        int gap = (processes[i].burst * 2) - (ganttTime > 9 ? 2 : 1);
        for (int j = 0; j < gap / 2 + 1; ++j)
            printf(" ");
        printf("%d", ganttTime);
        for (int j = 0; j < gap - gap / 2; ++j)
            printf(" ");
    }
    printf("\n");
    free(isCompleted);
}

int main()
{
    int numProcesses;
    printf("\t*****NISHAN DHAKAL*****\n******SJF Scheduling Algorithm******\n\nEnter the number of processes: ");
    scanf("%d", &numProcesses);
    Process *processes = (Process *)malloc(numProcesses * sizeof(Process));
    printf("Enter the process ID (character), arrival time, and burst time for each process:\n");
    for (int i = 0; i < numProcesses; ++i)
    {
        printf("For Process %d: ", i + 1);
        scanf(" %c %d %d", &processes[i].id, &processes[i].arrival, &processes[i].burst);
    }
    calculateSJF(processes, numProcesses);
    free(processes);
    return 0;
}
