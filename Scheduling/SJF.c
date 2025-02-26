#include <stdio.h>

struct Process {
    int pid, arrival, burst, completion, waiting, turnaround;
};

void sortByBurst(struct Process p[], int n, int start) {
    for (int i = start; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].burst > p[j].burst && p[j].arrival <= p[start - 1].completion) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void sjfScheduling(struct Process p[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        sortByBurst(p, n, i);
        if (time < p[i].arrival)
            time = p[i].arrival;
        p[i].completion = time + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        time = p[i].completion;
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
    }
    sjfScheduling(p, n);
    display(p, n);
    return 0;
}
