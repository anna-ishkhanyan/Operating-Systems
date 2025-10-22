#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
};

void fcfs(struct Process p[], int n) {
    printf("\n=== First Come First Served (FCFS) ===\n");

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival_time > p[j].arrival_time) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;

    printf("Gantt Chart: ");
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival_time)
            time = p[i].arrival_time;

        printf("| P%d ", p[i].pid);

        p[i].waiting_time = time - p[i].arrival_time;
        p[i].response_time = p[i].waiting_time;
        time += p[i].burst_time;
        p[i].turnaround_time = time - p[i].arrival_time;

        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
        total_rt += p[i].response_time;
    }
    printf("|\n");

    printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].waiting_time, p[i].turnaround_time, p[i].response_time);
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Response Time: %.2f\n", total_rt / n);
}

void sjf(struct Process p[], int n) {
    printf("\n=== Shortest Job First (SJF) ===\n");

    int completed_count = 0, time = 0;
    float total_wt = 0, total_tat = 0, total_rt = 0;
    int completed[n];

    for (int i = 0; i < n; i++) completed[i] = 0;

    printf("Gantt Chart: ");
    while (completed_count < n) {
        int pos = -1;
        int min_bt = 99999;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !completed[i]) {
                if (p[i].burst_time < min_bt) {
                    min_bt = p[i].burst_time;
                    pos = i;
                } else if (p[i].burst_time == min_bt &&
                           p[i].arrival_time < p[pos].arrival_time) {
                    pos = i;
                }
            }
        }

        if (pos == -1) {
            time++;
            continue;
        }

        printf("| P%d ", p[pos].pid);
        p[pos].waiting_time = time - p[pos].arrival_time;
        if (p[pos].waiting_time < 0)
            p[pos].waiting_time = 0;
        p[pos].response_time = p[pos].waiting_time;
        time += p[pos].burst_time;
        p[pos].turnaround_time = time - p[pos].arrival_time;
        completed[pos] = 1;
        completed_count++;

        total_wt += p[pos].waiting_time;
        total_tat += p[pos].turnaround_time;
        total_rt += p[pos].response_time;
    }
    printf("|\n");

    printf("PID\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].waiting_time, p[i].turnaround_time, p[i].response_time);
    }
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Response Time: %.2f\n", total_rt / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    }

    struct Process fcfs_p[n], sjf_p[n];
    for (int i = 0; i < n; i++) fcfs_p[i] = p[i];
    for (int i = 0; i < n; i++) sjf_p[i] = p[i];

    fcfs(fcfs_p, n);
    sjf(sjf_p, n);

    return 0;
}


 // Acknowledgment: as reference and guidance used code chunks from following sources:
// https://www.edureka.co/blog/first-come-first-serve-scheduling/
// https://www.sanfoundry.com/c-program-sjf-scheduling/#google_vignette