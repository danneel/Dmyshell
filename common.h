
#ifndef _COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

#define normal 0
#define out_redirect 1
#define in_redirect 2
#define have_pipe 3
#define pipe_out 4
#define appand 5
#define pipe_redirect 7
#define pipe_appand 8

void print_prompt();
void get_input(char *);
void explain_input(char *, int *, char arglist[100][256]);
void do_cmd(int, char arglist[][256]);
int find_command(char *);


#define _COMMON_H
#endif
