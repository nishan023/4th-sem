#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;
template <typename T>
struct Process
{
    T id;
    int arrival, burst, remaining, start, finish, waiting, turnaround;
};
template <typename T>
void calculateRoundRobin(vector<Process<T>> &processes, int quantum)
{
    int n = processes.size(), totalWaitingTime = 0, totalTurnaroundTime = 0, currentTime = 0, completedProcesses = 0;
    vector<bool> completed(n, false);
    vector<pair<T, int>> ganttChart; // Pair of process ID and time

    for (auto &p : processes)
        p.remaining = p.burst;

    while (completedProcesses < n)
    {
        bool progressMade = false;
        for (int i = 0; i < n; ++i)
        {
            if (!completed[i] && processes[i].arrival <= currentTime)
            {
                if (processes[i].remaining > 0)
                {
                    progressMade = true;
                    int timeSlice = min(quantum, processes[i].remaining);
                    processes[i].remaining -= timeSlice;
                    currentTime += timeSlice;
                    ganttChart.emplace_back(processes[i].id, currentTime);

                    if (processes[i].remaining == 0)
                    {
                        processes[i].finish = currentTime;
                        processes[i].turnaround = processes[i].finish - processes[i].arrival;
                        processes[i].waiting = processes[i].turnaround - processes[i].burst;
                        totalWaitingTime += processes[i].waiting;
                        totalTurnaroundTime += processes[i].turnaround;
                        completed[i] = true;
                        completedProcesses++;
                    }
                    if (processes[i].remaining == processes[i].burst - timeSlice)
                        processes[i].start = currentTime - timeSlice;
                }
            }
        }
        if (!progressMade)
            currentTime++;
    }
    cout << "\nGantt Chart:\n+";
    for (size_t i = 0; i < ganttChart.size(); ++i)
        cout << "-----+";
    cout << "\n|";
    for (const auto &p : ganttChart)
        cout << "  " << p.first << "  |";
    cout << "\n+";
    for (size_t i = 0; i < ganttChart.size(); ++i)
        cout << "-----+";
    cout << "\n0";
    for (const auto &p : ganttChart)
        cout << setw(6) << right << p.second;
    cout << "\n\nProcess Information:\n"
         << "---------------------------------------------------------------\n"
         << left << setw(10) << "Process" << "|" << setw(15) << "A.T" << "|" << setw(15) << "W.T" << "|" << setw(20) << "T.A.T" << "|\n"
         << "---------------------------------------------------------------\n";
    for (const auto &p : processes)
        cout << left << setw(10) << p.id << "|" << setw(15) << p.arrival << "|" << setw(15) << p.waiting << "|" << setw(20) << p.turnaround << "|\n";
    cout << "---------------------------------------------------------------\n";
    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << (float)totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << (float)totalTurnaroundTime / n << endl;
}

int main()
{
    int numProcesses, timeQuantum;
    char type;

    cout << "\t*****NISHAN DHAKAL*****\n"
         << "******Round Robin Scheduling Algorithm******\n\n"
         << "Enter the number of processes: ";
    cin >> numProcesses;
    cout << "Enter the type of Process IDs: ";
    cin >> type;
    cout << "Enter the time quantum: ";
    cin >> timeQuantum;
    vector<Process<char>> processes(numProcesses);
    cout << "\nEnter the process ID (character), arrival time, and burst time for each process (all in one line):\n";
    for (int i = 0; i < numProcesses; ++i)
    {
        cout << "For Process " << i + 1 << ": ";
        cin >> processes[i].id >> processes[i].arrival >> processes[i].burst;
    }
    calculateRoundRobin(processes, timeQuantum);

    return 0;
}
