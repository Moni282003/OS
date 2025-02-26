#include <stdio.h>
#include <limits.h>

struct Process {
    int pid, arrival, burst, remaining, completion, waiting, turnaround;
};

void srtfScheduling(struct Process p[], int n) {
    int completed = 0, time = 0, minIndex;
    while (completed < n) {
        int minBurst = INT_MAX;
        minIndex = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < minBurst) {
                minBurst = p[i].remaining;
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
    printf("PID\tArrival\tBurst\tCompletion\tTAT\tWaiting\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
    }
    srtfScheduling(p, n);
    display(p, n);
    return 0;
}
