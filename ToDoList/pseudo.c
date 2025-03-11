#include <stdio.h>

typedef struct{
    int year;
    int month;
    int day;
    int hour;
} date;

typedef struct{
    int id;
    char description[150];
    date deadline;
    int status;
} task;


int main(){
    /*
    print out the available options (formatted)
        printf("\nTo-Do List Manager\n");
        printf("1. Add Task\n");
        printf("2. View Pending Tasks\n");
        printf("3. View Completed Tasks\n");
        printf("4. Mark Task as Completed\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");  
    collect a input from the user
    create a switch case
    for pending and competed tasks, use view tasks, the argument will make the difference
    */
}


void add_task(){

    /*
    open file in append mode
    initiate task struct
    populate the struct with necessary information from the user
    for each line, write the information sep by a delimeter
    */
}

void viewTasks(completed){
    /*
    read in the file
    if completed is 0 (not completed)
        print pending tasks
        read in the information from the file
        use a if statement to print out tasks whose completed from stuct is equal to value passed
        close the file
    */
}
 void markascompleted(){

    /*
    open filel in read and write mode (r+)
    if !file, print no task found
    request for id to mark as completed
    loop through the lines of the file to where it matches the id
        if not completed, mark as completed
        seek to the position in file
        update as completed in file
        close the file 
    */
 }