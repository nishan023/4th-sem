#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
#include <string>

using namespace std;

template <typename T>
struct Process
{
    T id;           // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int remaining;  // Remaining Burst Time
    int start;      // Start Time
    int finish;     // Finish Time
    int waiting;    // Waiting Time
    int turnaround; // Turnaround Time
};

template <typename T>
void calculateRoundRobin(vector<Process<T>> &processes, int quantum)
{
    int n = processes.size();
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    int currentTime = 0;
    vector<bool> completed(n, false);
    int completedProcesses = 0;
    vector<int> ganttChart;
    vector<int> ganttTimes;

    // Initialize remaining times
    for (auto &p : processes)
    {
        p.remaining = p.burst;
    }

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
                    ganttChart.push_back(processes[i].id);
                    ganttTimes.push_back(currentTime);

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

                    // Mark start time for the first slice
                    if (processes[i].remaining == processes[i].burst - timeSlice)
                    {
                        processes[i].start = currentTime - timeSlice;
                    }
                }
            }
        }

        if (!progressMade)
        {
            currentTime++;
        }
    }

    // Display Gantt chart
    cout << "\nGantt Chart:\n";
    // Top border
    cout << "+";
    for (const auto &id : ganttChart)
    {
        cout << "-----+";
    }
    cout << endl;

    // Process IDs
    cout << "|";
    for (const auto &id : ganttChart)
    {
        cout << "  " << id << "  |";
    }
    cout << endl;

    // Middle border
    cout << "+";
    for (const auto &id : ganttChart)
    {
        cout << "-----+";
    }
    cout << endl;

    // Time line
    cout << 0;
    for (const auto &time : ganttTimes)
    {
        cout << setw(6) << right << time;
    }
    cout << endl;

    // Display process information and average calculations
    cout << "\nProcess Information:\n";
    cout << "---------------------------------------------------------------" << endl;
    cout << left << setw(10) << "Process" << "|" << setw(15) << "A.T"
         << "|" << setw(15) << "W.T" << "|" << setw(20) << "T.A.T" << "|" << endl;
    cout << "---------------------------------------------------------------" << endl;
    for (const auto &p : processes)
    {
        cout << left << setw(10) << p.id
             << "|" << setw(15) << p.arrival
             << "|" << setw(15) << p.waiting
             << "|" << setw(20) << p.turnaround << "|" << endl;
    }

    cout << "---------------------------------------------------------------" << endl;

    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << (float)totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << (float)totalTurnaroundTime / n << endl;
}

int main()
{
    int numProcesses;
    int timeQuantum;
    char type;

    cout << "\n<<Round Robin Scheduling Algorithm>>\n"
         << endl;
    cout << "Compiled by Suman Bisunkhe\n"
         << endl;

    cout << "Enter the type of Process IDs ('i' for integers, 'c' for characters): ";
    cin >> type;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    if (type != 'i' && type != 'c')
    {
        cout << "Invalid type. Exiting program." << endl;
        return 1;
    }
    cout << "Enter the time quantum: ";
    cin >> timeQuantum;

    if (type == 'i')
    {
        vector<Process<int>> processes(numProcesses);
        cout << "\nEnter the process ID, arrival time, and burst time for each process (all in one line):\n";
        for (int i = 0; i < numProcesses; ++i)
        {
            cout << "For Process " << i + 1 << ": ";
            cin >> processes[i].id >> processes[i].arrival >> processes[i].burst;
        }

        calculateRoundRobin(processes, timeQuantum);
    }
    else if (type == 'c')
    {
        vector<Process<char>> processes(numProcesses);
        cout << "\nEnter the process ID (character), arrival time, and burst time for each process (all in one line):\n";
        for (int i = 0; i < numProcesses; ++i)
        {
            cout << "For Process " << i + 1 << ": ";
            cin >> processes[i].id >> processes[i].arrival >> processes[i].burst;
        }

        calculateRoundRobin(processes, timeQuantum);
    }

    return 0;
}
