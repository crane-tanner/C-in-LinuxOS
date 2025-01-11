#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <signal.h>

sem_t semaphore;
pthread_t monitor_thread;
int thread_result = 0;

void* monitor_thread_function(void* arg) {
    sleep(10); // Sleep for 10 seconds
    if(sem_trywait(&semaphore) == 0) {
        printf("Monitor thread: Successfully acquired the semaphore.\n");
        sem_post(&semaphore);
        thread_result = 0;
    } else {
        printf("Monitor thread: Failed to acquire the semaphore.\n");
        thread_result = 1;
    }
    pthread_exit(&thread_result);
}

void child_process() {
    sem_wait(&semaphore); // Lock the semaphore
    printf("Child process: Acquired the semaphore and entering sleep.\n");
    sleep(60); // Simulate long-running process
    printf("Child process: Releasing the semaphore.\n");
    sem_post(&semaphore); // Release the semaphore
    exit(0);
}

int main() {
    pid_t pid;

    // Initialize the semaphore with an initial value of 1
    sem_init(&semaphore, 1, 1);

    pid = fork();

    if(pid < 0) {
        perror("fork failed");
        exit(1);
    } else if(pid == 0) {
        // Child process
        child_process();
    } else {
        // Parent process
        pthread_create(&monitor_thread, NULL, monitor_thread_function, NULL);

        int* thread_return_value;
        pthread_join(monitor_thread, (void**)&thread_return_value);

        if(*thread_return_value == 1) {
            printf("Parent process: Killing the child process.\n");
            kill(pid, SIGKILL);
            waitpid(pid, NULL, 0);
            printf("Parent process: Checking semaphore availability after killing child.\n");
            if(sem_trywait(&semaphore) == 0) {
                printf("Parent process: Successfully acquired the semaphore after killing child.\n");
                sem_post(&semaphore);
            } else {
                printf("Parent process: Failed to acquire the semaphore even after killing child.\n");
            }
        } else {
            waitpid(pid, NULL, 0);
        }

        // Destroy the semaphore
        sem_destroy(&semaphore);
        printf("Parent process: Semaphore destroyed and program exiting.\n");
    }

    return 0;
}
