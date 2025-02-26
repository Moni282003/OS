#include <stdio.h>
#include <limits.h>

struct Process {
    int pid, arrival, burst, remaining, priority, completion, waiting, turnaround;
};

void priorityPreemptiveScheduling(struct Process p[], int n) {
    int completed = 0, time = 0, minIndex;
    while (completed < n) {
        int minPriority = INT_MAX;
        minIndex = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].priority < minPriority) {
                minPriority = p[i].priority;
                minIndex = i;
            }
        }
        if (minIndex == -1) {
            time++;
            continue;
        }
        p[minIndex].remaining--;
        if (p[minIndex].remaining == 0) {
            p[minIndex].completion = time + 1;
            p[minIndex].turnaround = p[minIndex].completion - p[minIndex].arrival;
            p[minIndex].waiting = p[minIndex].turnaround - p[minIndex].burst;
            completed++;
        }
        time++;
    }
}

void display(struct Process p[], int n) {
    printf("PID\tArrival\tBurst\tPriority\tCompletion\tTAT\tWaiting\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].priority, p[i].completion, p[i].turnaround, p[i].waiting);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    printf("Enter Arrival Time, Burst Time, and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].priority);
        p[i].remaining = p[i].burst;
    }
    priorityPreemptiveScheduling(p, n);
    display(p, n);
    return 0;
}
