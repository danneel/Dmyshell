
#include "common.h"

void get_input(char *buf){
    int len = 0;
    int ch;

    ch = getchar();
    while (len < 256 && ch != '\n'){
        buf[len++] =ch;
        ch = getchar();
    }

    if (len == 256){
        printf("command is too long.\n");
        exit(-1);
    }
    buf[len] = '\n';
    len++;
    buf[len] = '\0';

}

