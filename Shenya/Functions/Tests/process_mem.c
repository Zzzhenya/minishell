#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void child_process(char *name) 
{
  char *new;
  new = NULL;
  new = (char *)malloc(strlen(name) + 1);
  strncpy(new, name, strlen(name) + 1);
  printf("%s\n", name);
  free(new);
}

void parent_process(char *name) 
{
    printf("%s\n", name);
}

void make_process(char *name) 
{
  pid_t pid;

  pid = fork();
  if (pid == -1)
    printf("fork() error\n");
  else if (pid == 0) 
  {
    child_process(name);
  }
  else 
  {
    waitpid(pid, NULL, WNOHANG);
    parent_process(name);
  }
}

int main(void) 
{
  char *name;

  name = NULL;
  name = strdup("WORD");
  make_process(name);
  free (name);
  return (0);
}