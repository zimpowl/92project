#include "../include/executor.h"

int exec(char *args[])
{
  int status;
  pid_t pid = fork();
  if (pid == -1)
    exit(EXIT_FAILURE);
  else if (pid > 0)
  {
    waitpid(-1, &status, 0);
    return WEXITSTATUS(status) & 0x7F;
  }
  else
  {
    status = execvp(args[0], args);
    exit(status);
  }
  if (WIFEXITED(status))
    exit(WEXITSTATUS(status));
  exit(EXIT_FAILURE);
}
