// write a simple program to implement longest remaining time first and find the avg turnaround time, 
// waiting time, completion time and response time  for overall process. also make the gantt chart

#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
    int started;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d%d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].pid = i + 1;
        p[i].remainingTime = p[i].burstTime;
        p[i].started = 0;
    }

    int completed = 0, currentTime = 0;
    float totalTAT = 0, totalWT = 0, totalCT = 0, totalRT = 0;
    int lastProcess = -1;

    printf("\nGantt Chart:\n|");

    while (completed < n) {
        int idx = -1;
        int maxRT = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && p[i].remainingTime > 0) {
                if (p[i].remainingTime > maxRT) {
                    maxRT = p[i].remainingTime;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            if (p[idx].started == 0) {
                p[idx].responseTime = currentTime - p[idx].arrivalTime;
                if (p[idx].responseTime < 0) p[idx].responseTime = 0;
                p[idx].started = 1;
            }

            if (lastProcess != p[idx].pid) {
                printf(" P%d |", p[idx].pid);
                lastProcess = p[idx].pid;
            }

            p[idx].remainingTime--;
            currentTime++;

            if (p[idx].remainingTime == 0) {
                p[idx].completionTime = currentTime;
                p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
                p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;

                totalTAT += p[idx].turnaroundTime;
                totalWT += p[idx].waitingTime;
                totalCT += p[idx].completionTime;
                totalRT += p[idx].responseTime;

                completed++;
            }
        } else {
            currentTime++; // CPU idle time
        }
    }

    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid,
            p[i].arrivalTime,
            p[i].burstTime,
            p[i].completionTime,
            p[i].turnaroundTime,
            p[i].waitingTime,
            p[i].responseTime
        );
    }

    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Completion Time: %.2f\n", totalCT / n);
    printf("Average Response Time: %.2f\n", totalRT / n);

    return 0;
}