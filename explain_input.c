
#include "common.h"


//将输入的命令进行分割保存在数组中，并且记下参数的个数
void explain_input(char *buf, int *argcount, char arglist[100][256]){
    char *p = buf;
    char *q = buf;
    int len = 0;
    *argcount = 0;

    while (1){
        if (p[0] == '\n'){
            break;
        }
        if(p[0] == ' '){
            p++;
        }else{
            q = p;
            len = 0;
            while ((q[0] != ' ')&& (q[0] != '\n')){
                len++;
                q++;
            }
            strncpy(arglist[*argcount], p, len+1);
            arglist[*argcount][len] = '\0';
            *argcount = *argcount+1;
            p = q;
        }
    }
    /*
    printf("%d\n", *argcount);
    for (int i = 0; i < *argcount; i++){
        printf("%s\n", arglist[i]);
    }*/

    return ;
}

