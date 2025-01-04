/* Programmer: Tanner Crane 
    Use of semaphore to control access to a "drive-thru" line
*/
#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX_CARS_IN_LINE 5
#define NUM_CARS 10

sem_t access_semaphore;

void* car_arrives(void* arg){
    int car_id = *(int*)arg; 

    sem_wait(&access_semaphore);

    printf("Car %d entering drive-thru line.\n", car_id);
    sleep(rand() % 3 + 1);
    printf("Car %d leaving drive-thru line.\n", car_id);

    sem_post(&access_semaphore);

   return NULL;
}

int main() {
sem_init(&access_semaphore, 0, MAX_CARS_IN_LINE);

pthread_t cars[NUM_CARS];
int car_ids[NUM_CARS];

for(int i = 0; i < NUM_CARS; i++) {
    car_ids[i] = i + 1; 
}
 
for(int i = 0; i < NUM_CARS; i++) {
    pthread_create(&cars[i], NULL, car_arrives, (void*)&car_ids[i]);

}

for(int i = 0; i < NUM_CARS; i++) {
    pthread_join(cars[i], NULL); 
}

sem_destroy(&access_semaphore);
return 0;
}

