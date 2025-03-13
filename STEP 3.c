#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

void readProcesses(Process processes[], int *n) {
    FILE *file = fopen("processes.txt", "r");
    if (!file) {
        printf("Error: Unable to open file.\n");
        return;
    }

    *n = 0;
    while (fscanf(file, "%d %d %d", &processes[*n].pid, &processes[*n].arrival_time,
                  &processes[*n].burst_time) == 3) {
        (*n)++;
    }
    fclose(file);
}

void displayGanttChart(Process processes[], int n) {
    int time = 0;
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        if (time < processes[i].arrival_time) {
            time = processes[i].arrival_time;
        }
        printf(" P%d |", processes[i].pid);
        time += processes[i].burst_time;
    }

    printf("\n0");
    time = 0;
    for (int i = 0; i < n; i++) {
        if (time < processes[i].arrival_time) {
            time = processes[i].arrival_time;
        }
        time += processes[i].burst_time;
        printf(" %d", time);
    }
    printf("\n");
}

void calculateTimes(Process processes[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < processes[i].arrival_time) {
            time = processes[i].arrival_time;
        }
        processes[i].waiting_time = time - processes[i].arrival_time;
        time += processes[i].burst_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
    }
}

void displayResults(Process processes[], int n) {
    int total_wt = 0, total_tat = 0;
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
        total_wt += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    Process processes[MAX_PROCESSES];
    int n;

    readProcesses(processes, &n);

    calculateTimes(processes, n);
    displayGanttChart(processes, n);
    displayResults(processes, n);

    return 0;
}
