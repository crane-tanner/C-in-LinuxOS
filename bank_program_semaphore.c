#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

//global variables
int BALANCE = 0; 
int transactions = 1000000;

//declare semaphore variable

sem_t semaphore; 


void* deposit_$1(void* args) {
 
    for(int i = 0; i < transactions; i++) {
           //create semaphore
    sem_wait(&semaphore);
        BALANCE += 1;
        sem_post(&semaphore); // release semaphore
}
return NULL; 
}
int main() {
    sem_init(&semaphore, 0, 1); // initialize binary semaphore
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
sem_destroy(&semaphore);
return 0;
}