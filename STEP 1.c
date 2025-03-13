#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
} Process;

// Function prototypes
void readProcesses(Process processes[], int *n);
void fcfs(Process processes[], int n);
void sjf(Process processes[], int n);
void calculateTimes(Process processes[], int n);
void displayResults(Process processes[], int n);

int main() {
    Process processes[MAX_PROCESSES];
    int n;

    readProcesses(processes, &n);

    printf("First-Come, First-Served (FCFS) Scheduling:\n");
    fcfs(processes, n);
    displayResults(processes, n);

    printf("\nShortest Job First (SJF) Scheduling:\n");
    sjf(processes, n);
    displayResults(processes, n);

    return 0;
}

void readProcesses(Process processes[], int *n) {
    FILE *file = fopen("processes.txt", "r");
    if (!file) {
        printf("Error: Unable to open file.\n");
        return;
    }

    *n = 0;
    while (fscanf(file, "%d %d %d %d", &processes[*n].pid, &processes[*n].arrival_time,
                  &processes[*n].burst_time, &processes[*n].priority) == 4) {
        (*n)++;
    }
    fclose(file);
}

void fcfs(Process processes[], int n) {
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

void sjf(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[j].burst_time < processes[i].burst_time) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
    fcfs(processes, n); // After sorting, follow FCFS logic
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
