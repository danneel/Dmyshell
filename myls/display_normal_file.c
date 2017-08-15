/*************************************************************************
	> File Name: display_normalfile.c
	> Author: danneel
	> Mail: 819253203@qq.com
	> Created Time: Mon May 15 10:14:53 2017
 ************************************************************************/

#include "common.h"

void display_normal_file(const char *filename, int param, struct stat *statbuf){
    int len = 0;
    //根据l参数进行展示
    if ((param == 3) || (param == 2)){
        char buf_time[32];
        struct passwd *psd;
        struct group *grp;
    
        //参数中有l,详细展示信息 
        if (S_ISLNK(statbuf->st_mode)){
            printf("l");
        }
        if (S_ISREG(statbuf->st_mode)){
            printf("-");
        }
        if (S_ISDIR(statbuf->st_mode)){
            printf("d");
        }
        if (S_ISCHR(statbuf->st_mode)){
            printf("c");
        }
        if (S_ISBLK(statbuf->st_mode)){
            printf("b");
        }
        if (S_ISFIFO(statbuf->st_mode)){
            printf("f");
        }
        if (S_ISSOCK(statbuf->st_mode)){
            printf("s");
        }

        if(statbuf->st_mode & S_IRUSR){
            printf("r");
        }else{
            printf("-");
        }
        if(statbuf->st_mode & S_IWUSR){
            printf("w");
        }else{
            printf("-");
        }
        if(statbuf->st_mode & S_IXUSR){
            printf("x");
        }else{
            printf("-");
        }

        if(statbuf->st_mode & S_IRGRP){
            printf("r");
        }else{
            printf("-");
        }
        if(statbuf->st_mode & S_IWGRP){
            printf("w");
        }else{
            printf("-");
        }
        if(statbuf->st_mode & S_IXGRP){
            printf("x");
        }else{
            printf("-");
        }
        
        if(statbuf->st_mode & S_IROTH){
            printf("r");
        }else{
            printf("-");
        }
        if(statbuf->st_mode & S_IWOTH){
            printf("w");
        }else{
            printf("-");
        }
        if(statbuf->st_mode & S_IXOTH){
            printf("x");
        }else{
            printf("-");
        }


        psd = getpwuid(statbuf->st_uid);
        grp = getgrgid(statbuf->st_gid);
        printf("%4d ", statbuf->st_nlink);
        printf("%-8s  ",psd->pw_name);
        printf("%-8s", grp->gr_name);

        printf("%6d ", statbuf->st_size);
        strcpy(buf_time, ctime(&statbuf->st_mtime));
        buf_time[strlen(buf_time) - 1] = 0;
        printf("%s ", buf_time);

        printf("%-s\n", filename);
    
    }
    else{ //根据参数处理单个文件
        if (leave_len < limitlen){
            printf("\n");
            leave_len = MAXROWLEN;
        }
        len = strlen(filename);
        leave_len -= len;
        printf("%-s", filename);
         for (int i = 0; i < (limitlen - len); i++){
             printf(" ");
         }
    }

    return;
}
