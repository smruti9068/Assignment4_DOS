/*Write a C program that will create three child process to perform the following operations
respectively:
- First child will copy the content of file1 to file2
- Second child will display the content of file2
- Third child will display the sorted content of file2 in reverse order.
- Each child process being created will display its id and its parent process id with
appropriate message.
- The parent process will be delayed for 1 second after creation of each child process. It
will display appropriate message with its id after completion of all the child processes*/ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// Function to copy the content of file1 to file2
void copy_file() {
    FILE *file1 = fopen("file1.txt", "r");
    FILE *file2 = fopen("file2.txt", "w");

    if (file1 == NULL || file2 == NULL) {
        perror("Error opening files");
        exit(1);
    }

    char ch;
    while ((ch = fgetc(file1)) != EOF) {
        fputc(ch, file2);
    }

    fclose(file1);
    fclose(file2);
    printf("Child %d (PID: %d) copied content from file1 to file2\n", getpid(), getppid());
}

// Function to display the content of file2
void display_file() {
    FILE *file2 = fopen("file2.txt", "r");

    if (file2 == NULL) {
        perror("Error opening file2");
        exit(1);
    }

    char ch;
    printf("Child %d (PID: %d) displaying content of file2:\n", getpid(), getppid());
    while ((ch = fgetc(file2)) != EOF) {
        putchar(ch);
    }

    fclose(file2);
}

// Function to display the sorted content of file2 in reverse order
void display_sorted_reverse() {
    FILE *file2 = fopen("file2.txt", "r");

    if (file2 == NULL) {
        perror("Error opening file2");
        exit(1);
    }

    // Read the content of file2 into an array of strings
    char lines[100][256];
    int i = 0;
    while (fgets(lines[i], sizeof(lines[i]), file2) != NULL) {
        i++;
    }
    fclose(file2);

    // Sort the lines in reverse order
    for (int j = 0; j < i - 1; j++) {
        for (int k = j + 1; k < i; k++) {
            if (strcmp(lines[j], lines[k]) < 0) {
                char temp[256];
                strcpy(temp, lines[j]);
                strcpy(lines[j], lines[k]);
                strcpy(lines[k], temp);
            }
        }
    }

    // Display the sorted content in reverse order
    printf("Child %d (PID: %d) displaying sorted content in reverse order:\n", getpid(), getppid());
    for (int j = 0; j < i; j++) {
        printf("%s", lines[j]);
    }
}

int main() {
    pid_t pid;

    // Create the first child to copy file1 to file2
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // First child process
        printf("Child %d (PID: %d) created by parent (PID: %d)\n", 1, getpid(), getppid());
        copy_file();
        exit(0);
    } else {
        // Parent process waits for 1 second after creating first child
        sleep(1);
    }

    // Create the second child to display content of file2
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Second child process
        printf("Child %d (PID: %d) created by parent (PID: %d)\n", 2, getpid(), getppid());
        display_file();
        exit(0);
    } else {
        // Parent process waits for 1 second after creating second child
        sleep(1);
    }

    // Create the third child to display sorted content of file2 in reverse order
    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Third child process
        printf("Child %d (PID: %d) created by parent (PID: %d)\n", 3, getpid(), getppid());
        display_sorted_reverse();
        exit(0);
    } else {
        // Parent process waits for 1 second after creating third child
        sleep(1);
    }

    // Parent waits for all child processes to finish
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    // After all children have completed, the parent process finishes
    printf("Parent (PID: %d) completed all child processes.\n", getpid());

    return 0;
}
