/*************************************************************************
	> File Name: handle_param.c
	> Author: danneel
	> Mail: 819253203@qq.com
	> Created Time: Sun May 14 00:42:52 2017
 ************************************************************************/

#include "common.h"

void handle_param(int argc, char **argv, int *flag_param, char path[][256]){
    int num = 0;
    int i = 0;
    int j = 0;
    char param[32];


    //分离ls的参数选项，并同时统计出现了多少个ls的参数选项
    for (i = 1; i < argc; i++){
        if (argv[i][0] == '-'){
            for (int k = 1; k < strlen(argv[i]); k++){
                param[j] = argv[i][k];
                j++;
            }
            num++;
        }
    }
    //形成一个关于ls参数的一个选项集合的数字表示
    for(i = 0; i < j; i++){
        if (param[i] == 'a'){
            *flag_param |= PARAM_A;
        }else if (param[i] == 'l'){
            *flag_param |= PARAM_L;
        }else{
            printf("出现错误的ls参数：%c, 请尝试正确的参数选项<a><l> 程序退出！\n", param[i]);
            exit(0);
        }
    }
    //查看是否输入了ls的目录或文件，默认当前文件
    if ((num + 1) == argc){
        strcpy(path, "./");
        filenum++;
        return;
    }
    //查找输入的目录文件
    for (i = 1; i < argc;i++){
        if (argv[i][0] != '-'){
            strcpy(path[filenum], argv[i]);
            filenum++;
        }
    }
    return ;



}
