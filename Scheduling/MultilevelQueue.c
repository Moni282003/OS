#include <stdio.h>

struct Process {
    int pid, arrival, burst, priority, queue, completion, waiting, turnaround;
};

void multilevelQueueScheduling(struct Process p[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].queue > p[j].queue || (p[i].queue == p[j].queue && p[i].arrival > p[j].arrival)) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival)
            time = p[i].arrival;
        p[i].completion = time + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        time = p[i].completion;
    }
}

void display(struct Process p[], int n) {
    printf("PID\tArrival\tBurst\tQueue\tCompletion\tTAT\tWaiting\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].queue, p[i].completion, p[i].turnaround, p[i].waiting);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    printf("Enter Arrival Time, Burst Time, and Queue Number (0 for System, 1 for User):\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].queue);
    }
    multilevelQueueScheduling(p, n);
    display(p, n);
    return 0;
}
