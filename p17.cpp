#include <stdio.h>

#define MAX_PROCESSES 100

void calculateWaitingTime(int burstTimes[], int numProcesses, int waitingTimes[]) {
    waitingTimes[0] = 0; // The first process has a waiting time of 0

    for (int i = 1; i < numProcesses; i++) {
        waitingTimes[i] = waitingTimes[i - 1] + burstTimes[i - 1];
    }
}
void calculateTurnaroundTime(int burstTimes[], int numProcesses, int waitingTimes[], int turnaroundTimes[]) {
    for (int i = 0; i < numProcesses; i++) {
        turnaroundTimes[i] = burstTimes[i] + waitingTimes[i];
    }
}
void calculateAverageTimes(int burstTimes[], int numProcesses) {
    int waitingTimes[MAX_PROCESSES];
    int turnaroundTimes[MAX_PROCESSES];
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    calculateWaitingTime(burstTimes, numProcesses, waitingTimes);
    calculateTurnaroundTime(burstTimes, numProcesses, waitingTimes, turnaroundTimes);

    for (int i = 0; i < numProcesses; i++) {
        totalWaitingTime += waitingTimes[i];
        totalTurnaroundTime += turnaroundTimes[i];
    }

    double averageWaitingTime = (double)totalWaitingTime / numProcesses;
    double averageTurnaroundTime = (double)totalTurnaroundTime / numProcesses;

    printf("Average Waiting Time: %.2f\n", averageWaitingTime);
    printf("Average Turnaround Time: %.2f\n", averageTurnaroundTime);
}
int main() {
    int burstTimes[MAX_PROCESSES];
    int numProcesses;

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    printf("Enter the burst times for each process:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &burstTimes[i]);
    }

    calculateAverageTimes(burstTimes, numProcesses);

    return 0;
}

