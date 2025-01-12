#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define RESOURCE_AVAILABLE 0 
#define RESOURCE_UNAVAILABLE 1 
#define MAX_WAIT_TIME 5 // in seconds

int resource = RESOURCE_AVAILABLE;
pthread_mutex_t mutex; 

void*process_func(void *arg) {
int pid = *(int*)arg; 
int wait_time = 0;

while(1) {
    pthread_mutex_lock(&mutex); 
    if(resource == RESOURCE_AVAILABLE) {
        fprintf(stderr, "Process %d acquired the resource.\n", pid); 
        resource = RESOURCE_UNAVAILABLE;
        pthread_mutex_unlock(&mutex); 

        //simulate using resource
        sleep(2);
        fprintf(stderr, "Process %d released resource.\n", pid); 
        resource = RESOURCE_AVAILABLE; 
        break; 
    }
    else {
        fprintf(stderr, "Process %d is waiting for the resource.\n", pid); 
        pthread_mutex_unlock(&mutex); 
        sleep(1); 
        wait_time++;
        if(wait_time >= MAX_WAIT_TIME){
            fprintf(stderr, "Process %d timed out.\n", pid); 
            exit(1); 
        }
    }
}
return NULL; 
}

int main() {
    pthread_t thread1, thread2; 
    int pid1 = 1, pid2 = 2;
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thread1, NULL, process_func, &pid1); 
    pthread_create(&thread2, NULL, process_func, &pid2);

    pthread_join(thread1, NULL); 
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;  
}