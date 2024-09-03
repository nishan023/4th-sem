#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum width for IDs and times
#define MAX_ID_WIDTH 10
#define MAX_TIME_WIDTH 10

typedef struct
{
    char id;
    int arrival, burst, start, finish, waiting, turnaround, priority;
} Process;

// Comparison function for sorting processes by arrival time and then by priority
int compareProcesses(const void *a, const void *b)
{
    Process *procA = (Process *)a;
    Process *procB = (Process *)b;
    if (procA->arrival == procB->arrival)
    {
        return procA->priority - procB->priority;
    }
    return procA->arrival - procB->arrival;
}
// Calculate Priority Scheduling
void calculatePriorityScheduling(Process *processes, int n)
{
    int totalWaitingTime = 0, totalTurnaroundTime = 0, currentTime = 0;
    int *completed = (int *)calloc(n, sizeof(int));
    qsort(processes, n, sizeof(Process), compareProcesses);
    while (1)
    {
        Process *currentProcess = NULL;
        for (int i = 0; i < n; ++i)
        {
            if (!completed[i] && processes[i].arrival <= currentTime)
            {
                if (currentProcess == NULL || processes[i].priority < currentProcess->priority)
                {
                    currentProcess = &processes[i];
                }
            }
        }
        if (currentProcess)
        {
            currentProcess->start = currentTime;
            currentProcess->finish = currentTime + currentProcess->burst;
            currentProcess->turnaround = currentProcess->finish - currentProcess->arrival;
            currentProcess->waiting = currentProcess->turnaround - currentProcess->burst;
            totalWaitingTime += currentProcess->waiting;
            totalTurnaroundTime += currentProcess->turnaround;
            currentTime = currentProcess->finish;
            completed[currentProcess - processes] = 1;
        }
        else if (1 == 1)
        { // This loop will break once all processes are completed
            int allDone = 1;
            for (int i = 0; i < n; ++i)
            {
                if (!completed[i])
                {
                    allDone = 0;
                    break;
                }
            }
            if (allDone)
                break;
            ++currentTime;
        }
    }
    free(completed);
    // Display Gantt Chart
    printf("\nGantt Chart:\n");
    printf("+");
    for (int i = 0; i < n; ++i)
    {
        printf("%*s+", MAX_TIME_WIDTH, "---------");
    }
    printf("\n");

    printf("|");
    for (int i = 0; i < n; ++i)
    {
        printf("%*c|", MAX_TIME_WIDTH, processes[i].id);
    }
    printf("\n");

    printf("+");
    for (int i = 0; i < n; ++i)
    {
        printf("%*s+", MAX_TIME_WIDTH, "---------");
    }
    printf("\n");

    printf("0");
    for (int i = 0; i < n; ++i)
    {
        printf("%*d", MAX_TIME_WIDTH, processes[i].finish);
    }
    printf("\n");

    // Display process information and average calculations
    printf("\nProcess Information:\n");
    printf("---------------------------------------------------------------\n");
    printf("%-10s| %-15s| %-15s| %-20s|\n", "Process", "A.T", "W.T", "T.A.T");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; ++i)
    {
        printf("%-10c| %-15d| %-15d| %-20d|\n", processes[i].id, processes[i].arrival, processes[i].waiting, processes[i].turnaround);
    }
    printf("---------------------------------------------------------------\n");
    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

int main()
{
    int numProcesses;
    printf("\t*****NISHAN DHAKAL*****\n******Priority Scheduling Algorithm******\n\nEnter the number of processes: ");
    scanf("%d", &numProcesses);

    Process *processes = (Process *)malloc(numProcesses * sizeof(Process));
    printf("\nEnter the process ID (character), arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < numProcesses; ++i)
    {
        printf("For Process %d: ", i + 1);
        scanf(" %c %d %d %d", &processes[i].id, &processes[i].arrival, &processes[i].burst, &processes[i].priority);
    }

    calculatePriorityScheduling(processes, numProcesses);

    free(processes);
    return 0;
}
