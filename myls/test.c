/*************************************************************************
	> File Name: test.c
	> Author: danneel
	> Mail: 819253203@qq.com
	> Created Time: Wed Jun 28 11:11:21 2017
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

int main(int argc, char *argv[]){
    printf("sbsbsbsb\n");
    sleep(3);
    printf("hahahahah\n");
    DIR *dir;
    struct dirent *ptr;
    if ((dir = opendir(".")) == NULL){
        printf("opendir error\n");
    }
    while((ptr = readdir(dir)) != NULL){
        printf("name - %s\n", ptr->d_name);
    }
    closedir(dir);

    return 0;
}


