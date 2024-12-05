#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
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
        printf("Parent, PID: %d\n", getpid());
        wait(NULL);  // Wait for child process to complete
        printf("Child process has terminated.\n");
    }

    return 0;
}
/*d) Modify the program so the parent waits for the child:  
     Here’s the modified code where the parent waits for the child to finish using wait().
     
After modification:
The parent prints its message once, waits for the child process to exit, and then displays that the child process has terminated. 
The child continues running.
*/