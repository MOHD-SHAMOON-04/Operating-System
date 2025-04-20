// Program to implement the priority queue scheduling algorithm using linked list

#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;        
    int priority;   // lower number = higher priority
    struct Process* next;
};

// to create a new process
struct Process* createProcess(int pid, int priority) {
    struct Process* newProcess = (struct Process*)malloc(sizeof(struct Process));
    newProcess->pid = pid;
    newProcess->priority = priority;
    newProcess->next = NULL;
    return newProcess;
}

// to insert a process based on priority
void insertProcess(struct Process** head, int pid, int priority) {
    struct Process* newProcess = createProcess(pid, priority);
    if (*head == NULL || priority < (*head)->priority) {
        newProcess->next = *head;
        *head = newProcess;
    } else {
        struct Process* temp = *head;
        while (temp->next != NULL && temp->next->priority <= priority) {
            temp = temp->next;
        }
        newProcess->next = temp->next;
        temp->next = newProcess;
    }
}

// to display the processes
void displayProcesses(struct Process* head) {
    printf("Process Execution Order (by Priority):\n");
    while (head != NULL) {
        printf("Process ID: %d, Priority: %d\n", head->pid, head->priority);
        head = head->next;
    }
}

// to free the linked list
void freeProcesses(struct Process* head) {
    struct Process* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Process* head = NULL;
    int n, pid, priority;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter Process ID and Priority (lower number = higher priority) for process %d: ", i + 1);
        scanf("%d%d", &pid, &priority);
        insertProcess(&head, pid, priority);
    }

    displayProcesses(head);

    freeProcesses(head);
    return 0;
}