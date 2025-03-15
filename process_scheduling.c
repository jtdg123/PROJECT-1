#include <stdio.h>

// Structure to represent a process
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to read processes from a file
int read_processes(const char* filename, Process processes[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        return -1;
    }

    int count = 0;
    char buffer[100];
    fgets(buffer, sizeof(buffer), file); // Skip header

    while (fscanf(file, "%d %d %d", &processes[count].pid, 
                  &processes[count].arrival_time, 
                  &processes[count].burst_time) != EOF) {
        count++;
    }

    fclose(file);
    return count;
}

// FCFS Scheduling
void fcfs(Process processes[], int n) {
    int time = 0;
    printf("Gantt Chart:\n");

    for (int i = 0; i < n; i++) {
        if (time < processes[i].arrival_time) {
            time = processes[i].arrival_time;
        }
        printf("| P%d ", processes[i].pid);
        processes[i].waiting_time = time - processes[i].arrival_time;
        processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
        time += processes[i].burst_time;
    }
    printf("|\n");
}

// SJF Scheduling
void sjf(Process processes[], int n) {
    int time = 0, completed = 0;
    printf("Gantt Chart:\n");

    while (completed < n) {
        int min_index = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].turnaround_time == 0) {
                if (min_index == -1 || processes[i].burst_time < processes[min_index].burst_time) {
                    min_index = i;
                }
            }
        }

        if (min_index != -1) {
            printf("| P%d ", processes[min_index].pid);
            processes[min_index].waiting_time = time - processes[min_index].arrival_time;
            processes[min_index].turnaround_time = processes[min_index].waiting_time + processes[min_index].burst_time;
            time += processes[min_index].burst_time;
            completed++;
        } else {
            time++; // No process available, increment time
        }
    }
    printf("|\n");
}

// Display Results
void display_results(Process processes[], int n) {
    printf("\nProcess\tWT\tTAT\n");
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\n", processes[i].pid, processes[i].waiting_time, processes[i].turnaround_time);
        total_wt += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    Process processes[100];
    int n = read_processes("processes.txt", processes);

    if (n == -1) return 1;

    int choice;
    printf("Choose a scheduling algorithm:\n");
    printf("1. First-Come, First-Served (FCFS)\n");
    printf("2. Shortest Job First (SJF)\n");
    printf("Enter choice: ");
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
