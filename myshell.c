
#include "common.h"

int main(int argc, char *argv[]){
    int i = 0;
    int argcount = 0;//参数个数
    char arglist[100][256];//参数集合
    char **arg = NULL;
    char *buf = NULL;

    buf = (char *)malloc(256);
    if (buf == NULL){
        perror("malloc error\n");
        exit(-1);
    }
    while (1){
        memset(buf, 0, 256);
        print_prompt();//输出提示符
        get_input(buf);//获取输入
        for (i = 0; i < 100; i++){
            arglist[i][0] = '\0';
        }
        argcount = 0;
        explain_input(buf, &argcount, arglist);//分析输入的命令
        do_cmd(argcount, arglist);
    }

    if (buf != NULL){
        free(buf);
        buf = NULL;
    }
    return 0;
}
