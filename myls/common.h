/*************************************************************************
	> File Name: common.h
	> Author: danneel
	> Mail: 819253203@qq.com
	> Created Time: Sun May 14 00:17:10 2017
 ************************************************************************/


#ifndef _COMMON_H
#define _COMMON_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>

#define PARAM_NONE 0
#define PARAM_A 1
#define PARAM_L 2
#define MAXROWLEN 80

extern int leave_len;
extern int limitlen;
extern int filenum;

void handle_param(int , char **, int *, char path[][256]);

void myerror(const char *, const char *, int);

void display_normal_file(const char *, int, struct stat *);

void display_dir(const char *, int);




#endif
