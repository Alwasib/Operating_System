#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid; // Process ID
    int burst_time;
    int arrival_time;
    int priority;
    int waiting_time = 0;
    int turnaround_time = 0;
    int response_time = -1; // -1 means not yet started
};

void roundRobinScheduling(vector<Process> &processes, int quantum)
{
    int n = processes.size();
    int currentTime = 0;
    double total_wt = 0, total_tat = 0, total_rt = 0;
    queue<int> q; // Queue to manage process indices
    vector<int> remaining_burst_time(n);
    vector<bool> in_queue(n, false); // Track if a process is in the queue

    // Initialize remaining burst time for each process
    for (int i = 0; i < n; i++)
    {
        remaining_burst_time[i] = processes[i].burst_time;
        if (processes[i].arrival_time <= currentTime)
        {
            q.push(i); // Enqueue process index if it has arrived
            in_queue[i] = true;
        }
    }

    while (!q.empty())
    {
        int i = q.front();
        q.pop();
        in_queue[i] = false; // Mark process as not in queue

        if (processes[i].response_time == -1)
        {
            processes[i].response_time = currentTime - processes[i].arrival_time;
        }

        // Check if process can complete within the time quantum
        if (remaining_burst_time[i] > quantum)
        {
            currentTime += quantum;
            remaining_burst_time[i] -= quantum;
        }
        else
        {
            currentTime += remaining_burst_time[i];
            processes[i].waiting_time = currentTime - processes[i].burst_time - processes[i].arrival_time;
            processes[i].turnaround_time = currentTime - processes[i].arrival_time;
            remaining_burst_time[i] = 0; // Process is done
        }

        // Enqueue processes that arrive during this time and are not already in queue
        for (int j = 0; j < n; j++)
        {
            if (j != i && remaining_burst_time[j] > 0 &&
                processes[j].arrival_time <= currentTime && !in_queue[j])
            {
                q.push(j);
                in_queue[j] = true; // Mark process as in queue
            }
        }

        // Re-enqueue the current process if it has remaining burst time
        if (remaining_burst_time[i] > 0)
        {
            q.push(i);
            in_queue[i] = true; // Mark process as in queue
        }
    }

    // Calculate total waiting, turnaround, and response times
    for (int i = 0; i < n; i++)
    {
        total_wt += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
        total_rt += processes[i].response_time;
    }

    cout << "\nRound Robin Scheduling Results:\n";
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

    int quant;
    cout << "Enter quantam time :" << endl;
    cin >> quant;

    vector<Process> roundProcess = processes;
    roundRobinScheduling(roundProcess, quant);

    return 0;
}
