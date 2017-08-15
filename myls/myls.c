/*************************************************************************
	> File Name: myls.c
	> Author: danneel
	> Mail: 819253203@qq.com
	> Created Time: Sun May 14 00:16:23 2017
 ************************************************************************/

#include "common.h"

int leave_len = MAXROWLEN;
int limitlen;
int filenum = 0;


int main(int argc, char *argv[]){
    int flag_param = PARAM_NONE;  //获取ls的参数的选项分析总和
    struct stat statbuf; //获取文件的信息

    char path[256][256]; //获取ls的路径名
    memset(path, 0, sizeof(path));

    handle_param(argc, argv, &flag_param, path);

    //根据文件的数目打印
    for (int i = 0; i < filenum; i++){
        if((lstat(path[i], &statbuf)) == -1){
            myerror("stat error", __FILE__,__LINE__);
        }
        if (S_ISDIR(statbuf.st_mode)){//目录文件
            printf("%-s:\n", path[i]);
            display_dir(path[i], flag_param);
        }else{//普通文件
            display_normal_file(path[i], flag_param,&statbuf);
        }
    }

    return 0;
}
