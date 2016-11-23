#include "../include/executor.h"

static int exec_pipe_cmd(char *args[], int income, int position)
{
  int pipes[2];
  pipe(pipes);
  pid_t pid = fork();
  if (pid == 0) 
  {
    if (position == 0 || position == 1) 
      dup2(pipes[1], STDOUT_FILENO);
    if (position == 1 || position == 2) 
      dup2(income, STDIN_FILENO);
    
    if (execvp(args[0], args) == -1)
      return (EXIT_FAILURE);
  }
  close(pipes[1]);
  if (position == 2)
    close(pipes[0]);
  if (income != 0) 
    close(income);
  return pipes[0];
}

void waiter(int nb)
{
  for (int i = 0; i < nb; ++i) 
    wait(NULL); 
}

int exec_pipe(char **args[])
{
    int position = 0;
    int income = 0;
    int i = 0;
    while (args[i + 1]) 
    {
      income = exec_pipe_cmd(args[i], income, position);
      position = 1;
      i++;
    }
    income = exec_pipe_cmd(args[i], income, 2);
    waiter(i + 1);
  return 0;
}

/*int main(void)
{
  char **argv[4];
  char *arg0[] = { "cat", "A", NULL };
  char *arg1[] = { "ls", NULL };
  char *arg2[] = { "wc", NULL };
  argv[0] = arg0;
  argv[1] = arg1;
  argv[2] = arg2;
  argv[3] = NULL;
  exec_pipe(argv);
  return 0;
}*/
