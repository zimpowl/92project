#ifndef _EXECUTOR_H
#define _EXECUTOR_H

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * @fn int exec(char *args[])
 * @param args is a list of string, they are commands to be executed.
 * @brief execute commands in a fork.
 * @return return the value of the given command.
 */
int exec(char *args[]);

/**
 * @fn int exec_pipe(char **args[])
 * @param args is a list of list of string, they are lists of commands.
 * @brief execute commands in a fork and pipe them.
 * @return return the value of the piped command.
 */
int exec_pipe(char **args[]);


/**
 * @fn int my_echo(ahcr *args[])
 * @brief
 */
int my_echo(char *args[]);

int my_export(char **args);
#endif
