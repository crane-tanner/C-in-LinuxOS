#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int counter = 0;
int misses = 0; 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* counter_thread(void* duration) {
    int runtime = *(int*)duration;
    time_t end = time(NULL) + runtime; 
    
    while(time(NULL) < end ){
        pthread_mutex_lock(&mutex);
        counter++;
        sleep(1); // sleep while mutex is on 
        pthread_mutex_unlock(&mutex);
    }
    printf("Counter thread finished. Final counter value: %d\n", counter);
    pthread_exit(NULL);
}

void* monitor_thread(void* duration) {
     int runtime = *(int*)duration;
    time_t end = time(NULL) + runtime; 
    
    while(time(NULL) < end) {
       sleep(3); 
       if(pthread_mutex_trylock(&mutex) == 0) {
            printf("Monitor thread: Counter value: %d\n", counter); 
            pthread_mutex_unlock(&mutex);
       }
       else {
        misses++;
       }
}
printf("Monitor thread has finished. Misses count: %d\n", misses); 
pthread_exit(NULL); 
}


int main() {
pthread_t counter_tid, monitor_tid; 
int runtime_minutes; 

printf("Enter runtime minutes: ");
scanf("%d", &runtime_minutes);
int runtime_seconds = runtime_minutes*60; 

pthread_create(&counter_tid, NULL, counter_thread, &runtime_seconds); 
pthread_create(&monitor_tid, NULL, monitor_thread, &runtime_seconds); 

pthread_join(counter_tid, NULL); 
pthread_join(monitor_tid, NULL); 

printf("Main program finished.\n");

return 0; 
}