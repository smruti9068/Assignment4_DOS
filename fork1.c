#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");/*The perror function in C is used to print a descriptive error message to stderr (standard error). 
                                It is commonly used to report the failure of system calls or library functions.
                                It prints a message that describes the last error that occurred, 
                                which is stored in the global variable errno.*/
        return 1;
    }

    if (pid == 0) {
        // Child process
        while(1) {
            printf("Child, PID: %d\n", getpid());
            sleep(1);
        }
    } else {
        // Parent process
        while(1) {
            printf("Parent, PID: %d\n", getpid());
            sleep(1);
        }
    }

    return 0;
}
/*Fork: The program creates a child process using the fork() system call. pid == 0 means the child process, 
  and pid > 0 means the parent process.
Infinite Loop: Both processes run in an infinite loop printing their process IDs.*/