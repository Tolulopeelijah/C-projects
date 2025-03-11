#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "tasks.txt"

// Define a struct for tasks
typedef struct {
    int id;
    char description[100];
    int completed;
} Task;

void addTask();
void viewTasks(int completed);
void markTaskCompleted();

int main() {
    int choice;
    while (1) {
        printf("\nTo-Do List Manager\n");
        printf("1. Add Task\n");
        printf("2. View Pending Tasks\n");
        printf("3. View Completed Tasks\n");
        printf("4. Mark Task as Completed\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks(0);
                break;
            case 3:
                viewTasks(1);
                break;
            case 4:
                markTaskCompleted();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void addTask() {
    FILE *file = fopen(FILE_NAME, "a"); // Open in append mode (text)
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    Task task;
    printf("Enter Task ID: ");
    scanf("%d", &task.id);
    getchar(); // Clear newline from buffer
    printf("Enter Task Description: ");
    fgets(task.description, 100, stdin);
    task.description[strcspn(task.description, "\n")] = 0; // Remove newline
    task.completed = 0;

    fprintf(file, "%d|%s|%d\n", task.id, task.description, task.completed);
    fclose(file);

    printf("Task added successfully!\n");
}


void viewTasks(int completed) {
    FILE *file = fopen(FILE_NAME, "rb"); // Open in read mode (text)
    if (!file) {
        printf("No tasks found.\n");
        return;
    }

    Task task;                     
    printf("\n%s Tasks:\n", completed ? "Completed" : "Pending");
    
    while (fscanf(file, "%d|%99[^|]|%d\n", &task.id, task.description, &task.completed) == 3) {
        if (task.completed == completed) {
            printf("ID: %d, Description: %s\n", task.id, task.description);
        }
    }
    fclose(file);
}


void markTaskCompleted() {
    
    FILE *file = fopen(FILE_NAME, "rb+"); // Read & write mode
    if (!file) {
        printf("No tasks found.\n");
        return;
    }


    int taskId;
    printf("Enter Task ID to mark as completed: ");
    scanf("%d", &taskId);

    Task task;


    while (fread(&task, sizeof(Task), 1, file)) {
        printf("%d", &task.id);

        if (task.id == taskId && task.completed == 0) {
            task.completed = 1;
            fseek(file, sizeof(Task), SEEK_CUR);
            fwrite(&task, sizeof(Task), 1, file);
            fclose(file);
            printf("Task marked as completed!\n");
            return;
        }
    }
    fclose(file);
    printf("Task not found or already completed.\n");
}




/*

id, title, description, year|month|day|hour|minutes


printf("%d, %s, %s, &d|%d|%d|%d|%d")

4 | a ml conference tomorrow | 56

"%d | %99[^|] | %d\n"
int | string  | int \n"

*/