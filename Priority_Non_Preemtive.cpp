#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid; // Process ID
    int burst_time;
    int arrival_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int response_time;
};

bool comparePriority(Process a, Process b)
{
    return a.priority < b.priority; // Sort by priority
}

void priorityScheduling(vector<Process> &processes)
{
    int n = processes.size();
    int currentTime = 0;
    double total_wt = 0, total_tat = 0, total_rt = 0;

    // Sort processes by priority
    sort(processes.begin(), processes.end(), comparePriority);

    for (int i = 0; i < n; i++)
    {
        if (currentTime < processes[i].arrival_time)
            currentTime = processes[i].arrival_time;

        processes[i].waiting_time = currentTime - processes[i].arrival_time;
        processes[i].response_time = processes[i].waiting_time;
        currentTime += processes[i].burst_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;

        total_wt += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
        total_rt += processes[i].response_time;
    }

    cout << "\nPriority Scheduling Results:\n";
    cout << "Average Waiting Time: " << total_wt / n << endl;
    cout << "Average Turnaround Time: " << total_tat / n << endl;
    cout << "Average Response Time: " << total_rt / n << endl;
}
int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    cout << "Enter Arival time | Burst Time | priority :" << endl;
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        cin >> processes[i].arrival_time;
        cin >> processes[i].burst_time;
        cin >> processes[i].priority;
    }

    vector<Process> priorityProcesses = processes;
    priorityScheduling(priorityProcesses);

    return 0;
}
