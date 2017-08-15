/*************************************************************************
	> File Name: myerror.c
	> Author: danneel
	> Mail: 819253203@qq.com
	> Created Time: Mon May 15 10:09:36 2017
 ************************************************************************/

#include "common.h"

void myerror(const char *errstring, const char *file, int flag){
    printf(stderr);
    perror(errstring);
    printf("from:%s -- %d\n", file, flag);
    exit(1);
}


