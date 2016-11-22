#include <stdio.h>
#include <stdlib.h>
#include "../include/tree.h"

int init_env(void)
{
  add_word(0, "HOME", getenv("HOME")); 
  add_word(0, "PWD", getenv("PWD")); 
  add_word(0, "OLDPWD", getenv("OLDPWD"));
  add_word(0, "IFS", getenv("IFS"));
  add_word(0, "PATH", getenv("PATH"));
  return 0;
}

int main(void)
{
  init_env();
  return 0;
}  
