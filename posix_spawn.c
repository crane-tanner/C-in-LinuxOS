#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <spawn.h>

int main(int argc, char *argv[]) {
  if(argc < 2) {
    fprintf(stderr, "Usage: %s <command>\n", argv[0]);
    return 1; 
  }
  char *const args[] = {argv[1], NULL};
  
  pid_t pid; 
  int status;
  
  if(posix_spawn(&pid, argv[1], NULL, NULL, args, NULL) != 0) {
  perror("posix_spawn failed");
  return 1;
  }
  
  printf("Child process ID: %d\n", pid); 
  
  if(waitpid(pid, &status, 0) == -1) {
    perror("waitpid failed");
    return 1;
  }
  
  if(WIFEXITED(status)) {
    printf("Child process exited with status: %d\n", WEXITSTATUS(status));
    
  }
  
  return 0;
}
