#include <stdio.h>
#include <stdbool.h>
struct process {
    int pid;    // Process ID
    int at;     // Arrival time
    int bt;     // Burst time
    int rt;     // Remaining time
    int wt;     // Waiting time
    int tat;    // Turnaround time
};
void traditional_rr(int n, struct process proc[], int tq) {
    int time = 0, count = 0;
    float total_wt = 0, total_tat = 0;
    while (count < n) {
        bool process_executed = false;
        for (int i = 0; i < n; i++) {
            if (proc[i].rt > 0 && proc[i].at <= time) {
                process_executed = true;
                printf("<%d>---P%d---", time, proc[i].pid);
                // Process execution for the time quantum or until completion
                int time_exec = (proc[i].rt > tq) ? tq : proc[i].rt;
                proc[i].rt -= time_exec;
                time += time_exec;
                // If process finishes
                if (proc[i].rt == 0) {
                    count++;
                    proc[i].tat = time - proc[i].at;
                    proc[i].wt = proc[i].tat - proc[i].bt;
                    total_wt += proc[i].wt;
                    total_tat += proc[i].tat;
                }
            }
        }

        // If no process is ready to execute, increment time
        if (!process_executed) {
            time++;
        }
    }

    printf("<%d>\n", time);
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n, tq;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process proc[n];
    printf("Enter time quantum: ");
    scanf("%d", &tq);

    for (int i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, and Burst Time for Process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].pid, &proc[i].at, &proc[i].bt);
        proc[i].rt = proc[i].bt;
        proc[i].wt = 0;
        proc[i].tat = 0;
    }

    printf("\nExecuting processes using Traditional Round Robin:\n");
    traditional_rr(n, proc, tq);

    return 0;
}
