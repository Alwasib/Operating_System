#include <iostream>
#include <climits>
using namespace std;
void firstFit(int partitions[], bool allocated[], int numPartitions, int processes[], int numProcesses) {
    cout << "\n<<<<<<<<<<First Fit Allocation>>>>>>>>>>\n";
    for (int i = 0; i < numProcesses; i++) {
        bool allocatedProcess = false;
        for (int j = 0; j < numPartitions; j++) {
            if (!allocated[j] && partitions[j] >= processes[i]) {
                cout << processes[i] << ": in " << partitions[j] << " partition <-> free space -> " << partitions[j] - processes[i] << "KB\n";
                partitions[j] -= processes[i];
                allocated[j] = true;
                allocatedProcess = true;
                break;
            }
        }
        if (!allocatedProcess) {
            cout << "**********Process " << i + 1 << " are in starvation**********\n";
        }
    }
}


void bestFit(int partitions[], bool allocated[], int numPartitions, int processes[], int numProcesses) {
    cout << "\n<<<<<<<<<<Best Fit Allocation>>>>>>>>>>\n";
    for (int i = 0; i < numProcesses; i++) {
        int bestIdx = -1;
        int minWaste = INT_MAX;
        for (int j = 0; j < numPartitions; j++) {
            if (!allocated[j] && partitions[j] >= processes[i] && partitions[j] - processes[i] < minWaste) {
                bestIdx = j;
                minWaste = partitions[j] - processes[i];
            }
        }
        if (bestIdx != -1) {
            cout << processes[i] << ": in " << partitions[bestIdx] << " partition <-> free space -> " << partitions[bestIdx] - processes[i] << "KB\n";
            partitions[bestIdx] -= processes[i];
            allocated[bestIdx] = true;
        } else {
            cout << "**********Process " << i + 1 << " are in starvation**********\n";
        }
    }
}
void worstFit(int partitions[], bool allocated[], int numPartitions, int processes[], int numProcesses) {
    cout << "\n<<<<<<<<<<Worst Fit Allocation>>>>>>>>>>\n";
    for (int i = 0; i < numProcesses; i++) {
        int worstIdx = -1;
        int maxWaste = -1;
        for (int j = 0; j < numPartitions; j++) {
            if (!allocated[j] && partitions[j] >= processes[i] && partitions[j] - processes[i] > maxWaste) {
                worstIdx = j;
                maxWaste = partitions[j] - processes[i];
            }
        }
        if (worstIdx != -1) {
            cout << processes[i] << ": in " << partitions[worstIdx] << " partition <-> free space -> " << partitions[worstIdx] - processes[i] << "KB\n";
            partitions[worstIdx] -= processes[i];
            allocated[worstIdx] = true;
        } else {
            cout << "**********Process " << i + 1 << " are in starvation**********\n";
        }
    }
}

int main() {
    int numPartitions, numProcesses;


    cout << "Enter number of partitions: ";
    cin >> numPartitions;
    int partitions[numPartitions];
    int originalPartitions[numPartitions];
    bool allocated[numPartitions];

     cout << "Enter number of processes: ";
    cin >> numProcesses;
    int processes[numProcesses];

    cout << "Enter the sizes of the partitions:\n";
    for (int i = 0; i < numPartitions; i++) {
        cin >> partitions[i];
        originalPartitions[i] = partitions[i];
        allocated[i] = false;
    }

    cout << "Enter the sizes of the processes:\n";
    for (int i = 0; i < numProcesses; i++) {
        cin >> processes[i];
    }


    firstFit(partitions, allocated, numPartitions, processes, numProcesses);


    for (int i = 0; i < numPartitions; i++) {
        partitions[i] = originalPartitions[i];
        allocated[i] = false;
    }


    bestFit(partitions, allocated, numPartitions, processes, numProcesses);


    for (int i = 0; i < numPartitions; i++) {
        partitions[i] = originalPartitions[i];
        allocated[i] = false;
    }


    worstFit(partitions, allocated, numPartitions, processes, numProcesses);

    return 0;
}
