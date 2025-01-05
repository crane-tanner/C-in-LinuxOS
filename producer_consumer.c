#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define BUFFER_SIZE 5

typedef struct {
    int buffer[BUFFER_SIZE];
    int in, out;
    sem_t mutex, full, empty;
} shared_data;

int main() {
    int shmid;
    shared_data *data;

    // creates shared memory segment
    shmid = shmget(IPC_PRIVATE, sizeof(shared_data), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // attach shared memory segment
    data = (shared_data *)shmat(shmid, NULL, 0);
    if (data == (void *) -1) {
        perror("shmat");
        exit(1);
    }

    // initialize semaphores
    sem_init(&data->mutex, 1, 1);
    sem_init(&data->full, 1, 0);
    sem_init(&data->empty, 1, BUFFER_SIZE);
    data->in = 0;
    data->out = 0;

    // create producer and consumer processes
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork fail");
        exit(1);
    }

    if (pid == 0) { // consumer child process
        int item;
        while (1) {
            sem_wait(&data->full);
            sem_wait(&data->mutex);

            item = data->buffer[data->out];
            data->out = (data->out + 1) % BUFFER_SIZE;

            printf("Consumed: %d\n", item);

            sem_post(&data->mutex);
            sem_post(&data->empty);
        }
    } else { // produce parent process
        int item = 0;
        while (1) {
            sem_wait(&data->empty);
            sem_wait(&data->mutex);

            data->buffer[data->in] = item++;
            data->in = (data->in + 1) % BUFFER_SIZE;

            printf("Produced: %d\n", item - 1);
            sleep(1);

            sem_post(&data->mutex);
            sem_post(&data->full);
        }
        wait(NULL);
    }

    return 0;
}