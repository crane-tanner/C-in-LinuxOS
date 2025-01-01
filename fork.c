#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed\n");
        return 1; 
    } else if (pid == 0) { 
        // Child process
        for (int i = 0; i < 10; i++) {
            printf("Child Process: Message %d\n", i);
            sleep(1); 
        }
        exit(0); 
    } else { 
        // Parent process
        for (int i = 0; i < 10; i++) {
            printf("Parent Process: Message %d\n", i);
            sleep(2); 
        }
        exit(0); // Add return 0; here
    }

    return 0; 
}