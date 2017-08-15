
#include "common.h"

int find_command(char *command){
    DIR *dp;
    struct dirent* dirp;

    char *path[] = {"./", "/bin", "/usr/bin", NULL};

    int i = 0;
    while(path[i] != NULL){
        if ((dp = opendir(path[i])) == NULL){
            printf("opendir error\n");
        }
        while((dirp = readdir(dp)) != NULL){
            if (strcmp(dirp->d_name, command) == 0){
                closedir(dp);
                return 1;
            }
        }
        closedir(dp);
        i++;
    }

    return 0;
}


