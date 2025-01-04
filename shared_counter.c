/* Programmer: Tanner Crane
Expected value is 500000
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 10

//global counter var

int counter = 0; 
pthread_mutex_t counter_mutex;

void* increaseby5_counter(void* args) {
for(int i = 0; i < 10000; i++) {
    pthread_mutex_lock(&counter_mutex);

    counter += 5; // increase by 5 each iteration **Critical Section

    pthread_mutex_unlock(&counter_mutex);
}

return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&counter_mutex, NULL); 

    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increaseby5_counter, NULL); 
    }

    // Wait for threads to finish
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value %d\n", counter); 

    pthread_mutex_destroy(&counter_mutex);
    return 0;
}