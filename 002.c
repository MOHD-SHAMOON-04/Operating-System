// Program to implement first come first serve scheduling algorithm and find the avg turnaround time, 
// waiting time, completion time and response time  for overall process. also make the gantt chart

#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].arrivalTime, &p[i].burstTime);
        p[i].pid = i + 1;
    }

    int currentTime = 0;
    float totalTAT = 0, totalWT = 0, totalCT = 0, totalRT = 0;

    printf("\nGantt Chart:\n|");

    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].arrivalTime) {
            currentTime = p[i].arrivalTime;
        }

        p[i].responseTime = currentTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].responseTime;
        currentTime += p[i].burstTime;
        p[i].completionTime = currentTime;
        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;

        totalTAT += p[i].turnaroundTime;
        totalWT += p[i].waitingTime;
        totalCT += p[i].completionTime;
        totalRT += p[i].responseTime;

        printf(" P%d |", p[i].pid);
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
