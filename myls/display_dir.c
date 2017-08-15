/*************************************************************************
	> File Name: display_dir.c
	> Author: danneel
	> Mail: 819253203@qq.com
	> Created Time: Mon May 15 11:23:02 2017
 ************************************************************************/

#include "common.h"


void display_dir(const char *filename, int param){
    DIR *dir;
    struct dirent *dirent;
    char filenames[256][256];
    char rawnames[256][256];
    char temp[256];

    memset(rawnames, '\0', 256*256);

    int filecount = 0;
    if ((dir = opendir(filename)) == NULL){
        myerror("opendir", __FILE__, __LINE__);
    }

    while((dirent = readdir(dir)) != NULL){
        if (limitlen < strlen(dirent->d_name)){
            limitlen = strlen(dirent->d_name) + 2;
        }
        filecount++;
    }
    closedir(dir);

    if (filecount > 256){
        myerror("more than 256 files", __FILE__, __LINE__);
    }

    //获取目录下的所有文件
    int len = strlen(filename);
    dir = opendir(filename);
    for (int i = 0; i < filecount; i++){
        dirent = readdir(dir);
        if (dirent == NULL){
            myerror("readdir", __FILE__, __LINE__);
        }
        strncpy(filenames[i], filename, len);
        filenames[i][len] = 0;
        strcat(filenames[i], dirent->d_name);
        strcpy(rawnames[i], dirent->d_name);
        filenames[i][len + strlen(dirent->d_name)] = 0;
    }
    
    //对所有文件进行排序
    for (int i = 0; i < filecount - 1; i++){
        for (int j = i + 1; j < filecount - 1; j++){
            if (strcmp(filenames[i], filenames[j]) > 0){
                strcpy(temp, filenames[j]);
                strcpy(filenames[j], filenames[i]);
                strcpy(filenames[i], temp);
            }
        }
    }
    for (int i = 0; i < filecount - 1; i++){
        for (int j = i + 1; j < filecount - 1; j++){
            if (strcmp(rawnames[i], rawnames[j]) > 0){
                strcpy(temp, rawnames[j]);
                strcpy(rawnames[j], rawnames[i]);
                strcpy(rawnames[i], temp);
            }
        }
    }

    struct stat statbuf;
    //对目录里的每个文件进行打印
    for (int i = 0; i < filecount; i++){
        if ((param == 0) || (param == 2)){   
            if (rawnames[i][0] != '.')
            {
                if (lstat(filenames[i], &statbuf) == -1){
                    myerror("stat error", __FILE__, __LINE__);
                    exit(-1);
                }
                display_normal_file(rawnames[i], param, &statbuf);
            }
        }else{
            if (lstat(filenames[i], &statbuf) == -1){
                myerror("stat error", __FILE__, __LINE__);
                exit(-1);
            }
            display_normal_file(rawnames[i], param, &statbuf);
        }
    }
    printf("\n");
    closedir(dir);

    return ;
}

