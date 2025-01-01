#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void main() {
fork();
fork();
printf("I am process id: %d\n", getpid());

}
