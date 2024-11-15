#include <bits/stdc++.h>
using namespace std;

class CompareRemainingTime
{
public:
    bool operator()(pair<int, int> left, pair<int, int> right)
    {
        return left.first > right.first;
    }
};

void calculateTimes(const vector<pair<int, int>> &processes, int n, vector<int> &completionTime, vector<int> &waitingTime, vector<int> &turnaroundTime, vector<int> &responseTime)
{
    vector<int> remainingTime(n);
    vector<bool> started(n, false), isInQueue(n, false);
    for (int i = 0; i < n; i++)
    {
        remainingTime[i] = processes[i].second;
    }

    int currentTime = 0;
    int completedProcesses = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareRemainingTime> pq;

    while (completedProcesses < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (processes[i].first <= currentTime && remainingTime[i] > 0 && !isInQueue[i])
            {
                pq.push({remainingTime[i], i});
                isInQueue[i] = true;
            }
        }

        if (pq.empty())
        {
            currentTime++;
            continue;
        }

        int minIndex = pq.top().second;
        pq.pop();

        if (!started[minIndex])
        {
            responseTime[minIndex] = currentTime - processes[minIndex].first;
            started[minIndex] = true;
        }

        remainingTime[minIndex]--;
        currentTime++;

        if (remainingTime[minIndex] == 0)
        {
            completionTime[minIndex] = currentTime;
            turnaroundTime[minIndex] = completionTime[minIndex] - processes[minIndex].first;
            waitingTime[minIndex] = turnaroundTime[minIndex] - processes[minIndex].second;
            completedProcesses++;
        }
        else
        {
            pq.push({remainingTime[minIndex], minIndex});
        }
    }
}

void printProcessDetails(const vector<pair<int, int>> &processes, int n, const vector<int> &completionTime, const vector<int> &waitingTime, const vector<int> &turnaroundTime, const vector<int> &responseTime)
{
    cout << "ID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\tResponse\n";
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << "\t" << processes[i].first << "\t" << processes[i].second
             << "\t" << completionTime[i] << "\t\t" << turnaroundTime[i]
             << "\t\t" << waitingTime[i] << "\t\t" << responseTime[i] << "\n";
    }
}

void printAvgDetails(int n, const vector<int> &turnaroundTime, const vector<int> &waitingTime, const vector<int> &responseTime)
{
    double avgTurnaroundTime = accumulate(turnaroundTime.begin(), turnaroundTime.end(), 0.0) / n;
    double avgWaitingTime = accumulate(waitingTime.begin(), waitingTime.end(), 0.0) / n;
    double avgResponseTime = accumulate(responseTime.begin(), responseTime.end(), 0.0) / n;

    cout << fixed << setprecision(2);
    cout << "Average Turnaround Time: " << avgTurnaroundTime << "\n";
    cout << "Average Waiting Time: " << avgWaitingTime << "\n";
    cout << "Average Response Time: " << avgResponseTime << "\n";
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<pair<int, int>> processes(n); // Each pair is <arrival time, burst time>
    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> processes[i].first >> processes[i].second;
    }

    vector<int> completionTime(n), waitingTime(n), turnaroundTime(n), responseTime(n);

    calculateTimes(processes, n, completionTime, waitingTime, turnaroundTime, responseTime);
    printProcessDetails(processes, n, completionTime, waitingTime, turnaroundTime, responseTime);
    printAvgDetails(n, turnaroundTime, waitingTime, responseTime);

    return 0;
}
