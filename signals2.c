#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#define BUFFER_SIZE 10
char shared_buffer[BUFFER_SIZE];
int in = 0, out = 0;
int count = 0;
pid_t parent_pid, child_pid;

void put(char data) {
    while(count == BUFFER_SIZE) {
        // Buffer is full, wait
        pause();
    }
    shared_buffer[in] = data;
    in = (in + 1) % BUFFER_SIZE;
    count++;
    kill(child_pid, SIGUSR1); // Signal to the child that data is available
}

char get() {
    while(count == 0) {
        // Buffer is empty, wait
        pause();
    }
    char data = shared_buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    count--;
    kill(parent_pid, SIGUSR2); // Signal to the parent that data has been consumed
    return data;
}

void producer(const char *message) {
    for(int i = 0; message[i] != '\0'; i++) {
        put(message[i]);
    }
    put('\0'); // Signal end of data
}

void consumer() {
    char c;
    while(1) {
        c = get();
        if(c == '\0') {
            break;
        }
        printf("%c", c);
    }
    printf("\n");
}

void signal_handler(int signum) {
    // Just catch and return
}

int main() {
    char *message = "Tanner";

    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    parent_pid = getpid();

    pid_t pid = fork();

    if(pid < 0) {
        perror("fork failed");
        exit(1);
    } else if(pid == 0) { // Child process
        child_pid = getpid();
        while(1) {
            pause(); // Wait for a signal from the parent
            consumer();
        }
    } else { // Parent process
        child_pid = pid;
        producer(message);
        wait(NULL); // Wait for child process to finish
    }

    return 0;
}
