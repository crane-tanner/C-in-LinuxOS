#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define WAKEUP SIGUSR1

void handler(int signum) {
  if(signum == WAKEUP) {
    printf("Child process: Received WAKEUP signal\n");
}
}

int main() {
pid_t pid = fork();

   if (pid < 0) {
        perror("Fork failed\n");
        return 1;  
    } 
    
    else if (pid == 0) { 
      signal(WAKEUP, handler);
      pause();
      
        for (int i = 0; i < 20; i++) {
            printf("Child Process: Message %d\n", i);
            sleep(1); 
        }
        exit(1); 
        }
    else {
      for(int i = 0; i < 30; i++) {
        printf("Parent process: Message %d\n", i);
        sleep(1);
        
        if(i == 5) {
          kill(pid, WAKEUP);
          printf("Parent Process: Sent WAKEUP signal to child \n");
          exit(1);
        }
      }
    }
    
    return 0;
}
