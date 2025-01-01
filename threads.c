#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function1(void *arg) {
for(int i = 1; i < 11; i++){
printf("Thread 1: Pass %d\n", i);
sleep(1);
}
pthread_exit(NULL);
}

void *thread_function2(void *args) {
for(int i = 1; i < 11; i++) {
printf("Thread 2: Pass %d\n", i);
sleep(2);
}
pthread_exit(NULL); 
}

int main() {
pthread_t thread_1, thread_2;

//Error handling 
if(pthread_create(&thread_1, NULL, thread_function1, NULL) != 0) {
perror("Error creating thread 1\n");
return 1;
}

if(pthread_create(&thread_2, NULL, thread_function2, NULL) !=0) {
perror("Error creating thread 2\n");
return 1;
}

pthread_join(thread_1, NULL); 
pthread_join(thread_2, NULL);

printf("Main thread exiting.\n");

return 0;
}
