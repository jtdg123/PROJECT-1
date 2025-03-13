#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

// Structure to hold process details
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to read process data from a file
int read_processes(Process processes[]) {
    FILE *file = fopen("processes.txt", "r");
    if (!file) {
        printf("Error: Could not open file.\n");
        exit(1);
    }

    int i = 0;
    while (fscanf(file, "%d %d %d", &processes[i].pid, &processes[i].arrival_time, &processes[i].burst_time) != EOF) {
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        i++;
    }

    fclose(file);
    return i;
}

// Function to sort processes by arrival time (FCFS)
void sort_by_arrival(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function to sort processes by burst time (SJF)
void sort_by_burst(Process processes[], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && processes[j].burst_time < processes[j - 1].burst_time; j--) {
            Process temp = processes[j];
            processes[j] = processes[j - 1];
            processes[j - 1] = temp;
        }
    }
}

// Function to calculate waiting and turnaround times for FCFS
void fcfs(Process processes[], int n) {
    sort_by_arrival(processes, n);

    int current_time = 0;
    printf("\nGantt Chart (FCFS):\n|");
    
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        printf(" P%d |", processes[i].pid);

        processes[i].waiting_time = current_time - processes[i].arrival_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;

        current_time += processes[i].burst_time;
    }

    printf("\n0");

    current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        current_time += processes[i].burst_time;
        printf("    %d", current_time);
    }

    printf("\n");
}

// Function to calculate waiting and turnaround times for SJF
void sjf(Process processes[], int n) {
    sort_by_burst(processes, n);

    int current_time = 0;
    printf("\nGantt Chart (SJF):\n|");

    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        printf(" P%d |", processes[i].pid);

        processes[i].waiting_time = current_time - processes[i].arrival_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;

        current_time += processes[i].burst_time;
    }

    printf("\n0");

    current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        current_time += processes[i].burst_time;
        printf("    %d", current_time);
    }

    printf("\n");
}

// Function to display process details
void display_results(Process processes[], int n) {
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", 
               processes[i].pid, 
               processes[i].arrival_time, 
               processes[i].burst_time, 
               processes[i].waiting_time, 
               processes[i].turnaround_time);
    }

    // Calculate average WT and TAT
    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += processes[i].waiting_time;
        avg_tat += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat / n);
}

int main() {
    Process processes[MAX_PROCESSES];
    int n = read_processes(processes);

    printf("Choose Scheduling Algorithm:\n1. First-Come, First-Served (FCFS)\n2. Shortest Job First (SJF)\n");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        fcfs(processes, n);
    } else if (choice == 2) {
        sjf(processes, n);
    } else {
        printf("Invalid choice.\n");
        return 1;
    }

    display_results(processes, n);
    return 0;
}
