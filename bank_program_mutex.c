#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//global variables
int BALANCE = 0; 
int transactions = 1000000;
pthread_mutex_t balance_mutex;
void* deposit_$1(void* args) {
    for(int i = 0; i < transactions; i++) {
        //create lock 
        pthread_mutex_lock(&balance_mutex);

        //critical section (accesss of shared resource)
        BALANCE += 1;

        //release lock
        pthread_mutex_unlock(&balance_mutex);
}
return NULL; 
}
int main() {
    pthread_t thread_1, thread_2; 

if(pthread_create(&thread_1, NULL, deposit_$1, NULL) != 0) {
    perror("Error creating thread 1\n"); 
    return 1;
}

if(pthread_create(&thread_2, NULL, deposit_$1, NULL) !=0) {
    perror("Error creating thread 2\n");
    return 1;
}
pthread_join(thread_1, NULL);
printf("First thread is finished.\n");
pthread_join(thread_2, NULL);
printf("Second thread is finished.\n");
printf("Bank account balance is: $%d\n", BALANCE);
// destory mutex to release resources 
pthread_mutex_destroy(&balance_mutex);
return 0;
}