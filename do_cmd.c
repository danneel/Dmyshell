
#include "common.h"
//将参数传进去，进行分析并执行
void do_cmd(int argcount, char arglist[100][256]){
    int flag = 0;
    int how = 0;
    int backgroud = 0;
    int status;
    int i;
    int fd;
    char *arg[argcount+1];
    char *argnex[argcount+1];
    char *file;
    pid_t pid;


    //将参数拷贝到本文件数组
    for (i = 0; i < argcount; i++){
        arg[i] = (char *)arglist[i];//arg参数列表将要进行修改
       // printf("%s\n", arg[i]);
    }
    arg[argcount] = NULL;
    //查找后台操作符
    for (i = 0; i < argcount;i++){
        if (strcmp(arg[i], "&") == 0){
            if (i == argcount-1){//保证操作符放在最后
                backgroud = 1;
                arg[argcount-1] = NULL;
                break;
            }else{
                printf("wrong command");
                return ;
            }
        }
    }
    //找定向符
    for(i = 0; arg[i] != NULL; i++){
        if(strcmp(arg[i], ">") == 0){
            if (how == have_pipe){
                how = pipe_redirect;
            }else{
                flag++;
                how = out_redirect;
                if(arg[i+1] == NULL || i == 0){
                    flag += 11;
                }
            }
        }
        if (strcmp(arg[i], "<") == 0){
            flag++;
            how = in_redirect;
            if(arg[i+1] == NULL ){
                flag += 11;
            }
        }
        if (strcmp(arg[i], "|") == 0){
            flag++;
            how = have_pipe;
            if (arg[i+1] == NULL){
                flag += 11;
            }
            if (i == 0){
                flag += 11;
            }
        }
        if (strcmp(arg[i], ">>") == 0){
            if (how == have_pipe){
                how = pipe_appand;
            }else{
                flag++;
                how = appand;
                if (arg[i+1] == NULL){
                    flag++;
                }
            }
        }
    }



    //不支持>后面没有操作数和<出现在第一个以及|出现在第一个以及在第一个或者后面没有的情况
    if (flag > 10){
        printf("wrong command\n");
        return ;
    }

    if (how == out_redirect){
        for (i = 0; arg[i] != NULL; i++){
            if (strcmp(arg[i], ">") == 0){
                file = arg[i+1];
                arg[i] = NULL;
            }
        }
    }
    if (how == appand){
        for (i = 0; arg[i] != NULL; i++){
            if (strcmp(arg[i], ">>") == 0){
                file = arg[i+1];
                arg[i] = NULL;
            }
        }
    }
    
    if (how == in_redirect){
        for (i = 0; arg[i] != NULL; i++){
            if (strcmp(arg[i], "<") == 0){
                file = arg[i+1];
                arg[i] = NULL;
            }
        }
    }
    if (how == pipe_redirect){
        for (i = 0; arg[i] != NULL; i++){
            if (strcmp(arg[i], "|") == 0){
                arg[i] = NULL;
                int j;
                for (j = i+1; ((arg[j] != NULL)); j++){
                    if (strcmp(arg[j], ">") == 0){
                        file = arg[j+1];
                        arg[j] = NULL;
                        j--;
                    }else{
                        argnex[j-i-1] = arg[j];
                    }
                }
                //argnex[j-i-1] = arg[j];
                break;
            }
        }
    }
    if (how == pipe_appand){
        for (i = 0; arg[i] != NULL; i++){
            if (strcmp(arg[i], "|") == 0){
                arg[i] = NULL;
                int j;
                for (j = i+1; ((arg[j] != NULL)); j++){
                    if (strcmp(arg[j], ">>") == 0){
                        file = arg[j+1];
                        arg[j] = NULL;
                        j--;
                    }else{
                        argnex[j-i-1] = arg[j];
                    }
                }
                //argnex[j-i-1] = arg[j];
                break;
            }
        }
    }
    if (how == have_pipe){
        for (i = 0; arg[i] != NULL; i++){
            if (strcmp(arg[i], "|") == 0){
                arg[i] = NULL;
                int j;
                for (j = i+1; arg[j] != NULL; j++){
                    argnex[j-i-1] = arg[j];
                }
                argnex[j-i-1] = arg[j];
                break;
            }
        }
    }


    if ((pid = fork()) < 0){
        printf("fork error\n");
        return;
    }
    switch(how){
        case 0:{
            if (pid == 0){
                if (!(find_command(arg[0]))){
                    printf("%s : command not found  %d\n", arg[0], __LINE__);
                    exit(0);
                }
                execvp(arg[0], arg);
                exit(0);
            }
            break;
        }
        case 1:{
            if (pid == 0){
                if (!(find_command(arg[0]))){
                    printf("%s : command not found  %d\n", arg[0], __LINE__);
                    exit(0);
                }
                fd = open(file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
                int fdnew = dup2(fd, 1);
                execvp(arg[0], arg);
                exit(0);
            }
            break;
        }
        case 5:{
            if (pid == 0){
                if (!(find_command(arg[0]))){
                    printf("%s : command not found  %d\n", arg[0], __LINE__);
                    exit(0);
                }
                fd = open(file, O_CREAT|O_WRONLY, 0644);
                lseek(fd, 0, SEEK_END);
                int fdnew = dup2(fd, 1);
                execvp(arg[0], arg);
                exit(0);
            }
            break;
        }
        case 7:{
            if (pid == 0){
                int pid2, pid3;
                int status2;
                int fd2;

                if ((pid2 = fork()) < 0){
                    printf("fork2 error\n");
                    return ;
                }else if(pid2 == 0){
                    if (!(find_command(arg[0]))){
                        printf("%s : command not found  %d\n", arg[0], __LINE__);
                        exit(0);
                    }
                    fd2 = open("youdonotknowfile", O_WRONLY|O_CREAT|O_TRUNC, 0644);
                    dup2(fd2, 1);

                    execvp(arg[0], arg);
                    exit(0);
                }
                if(waitpid(pid2, &status2, 0) == -1){
                    printf("wait for child process error1\n");
                }

                if ((pid2 = fork()) < 0){
                    printf("fork2 error\n");
                    return ;
                }else if(pid2 == 0){
                    if (!(find_command(argnex[0]))){
                        printf("%s : command not found  %d\n", argnex[0], __LINE__);
                        exit(0);
                    }
                    fd2 = open(file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
                    lseek(fd2, 0, SEEK_END);
                    char outfile[] = "youdonotknowfile";
                    argnex[1] = outfile;
                    argnex[2] = NULL;
                    dup2(fd2, 1);
                    execvp(argnex[0], argnex);
                    exit(0);
                }

                if(waitpid(pid2, &status2, 0) == -1){
                    printf("wait for child process error2\n");
                }
                
                if (remove("youdonotknowfile") == -1){
                    printf("remove file error\n");
                }
                printf("> ok!\n");
                exit(0);
            }
            break;
        }
        case 8:{
            if (pid == 0){
                int pid2, pid3;
                int status2;
                int fd2;

                if ((pid2 = fork()) < 0){
                    printf("fork2 error\n");
                    return ;
                }else if(pid2 == 0){
                    if (!(find_command(arg[0]))){
                        printf("%s : command not found  %d\n", arg[0], __LINE__);
                        exit(0);
                    }
                    fd2 = open("youdonotknowfile", O_WRONLY|O_CREAT|O_TRUNC, 0644);
                    dup2(fd2, 1);

                    execvp(arg[0], arg);
                    exit(0);
                }
                if(waitpid(pid2, &status2, 0) == -1){
                    printf("wait for child process error1\n");
                }

                if ((pid2 = fork()) < 0){
                    printf("fork2 error\n");
                    return ;
                }else if(pid2 == 0){
                    if (!(find_command(argnex[0]))){
                        printf("%s : command not found  %d\n", argnex[0], __LINE__);
                        exit(0);
                    }
                    fd2 = open(file, O_WRONLY|O_CREAT, 0644);
                    lseek(fd2, 0, SEEK_END);
                    char outfile[] = "youdonotknowfile";
                    argnex[1] = outfile;
                    argnex[2] = NULL;
                    dup2(fd2, 1);
                    execvp(argnex[0], argnex);
                    exit(0);
                }

                if(waitpid(pid2, &status2, 0) == -1){
                    printf("wait for child process error2\n");
                }
                if (remove("youdonotknowfile") == -1){
                    printf("remove file error\n");
                }
                printf(">> ok!\n");
                exit(0);
            }
            break;
        }
        case 2:{
            if (pid == 0){
                if (arg[0] == NULL){
                    arg[0] = "cat";
                    arg[1] = NULL;
                }
                if (!(find_command(arg[0]))){
                    printf("%s : command not found  %d\n", arg[0], __LINE__);
                    exit(0);
                }
                fd = open(file, O_RDONLY);
                dup2(fd, 0);
                execvp(arg[0], arg);
                exit(0);
            }
            break;
        }
        case 3:{
            if (pid == 0){
                int pid2;
                int status2;
                int fd2;

                if ((pid2 = fork()) < 0){
                    printf("fork2 error\n");
                    return ;
                }else if(pid2 == 0){
                    if (!(find_command(arg[0]))){
                        printf("%s : command not found  %d\n", arg[0], __LINE__);
                        exit(0);
                    }
                    fd2 = open("/tmp/youdonotknowfile", O_WRONLY|O_CREAT|O_TRUNC, 0644);
                    dup2(fd2, 1);
                    execvp(arg[0], arg);
                    exit(0);
                }
                
                if(waitpid(pid2, &status2, 0) == -1){
                    printf("wait for child process error3\n");
                }
                if (!(find_command(argnex[0]))){
                    printf("%s : command not found %d\n", argnex[0], __LINE__);
                    exit(0);
                }
                fd2 = open("/tmp/youdonotknowfile", O_RDONLY);
                dup2(fd2, 0);
                execvp(argnex[0], argnex);
                
                if (remove("/tmp/youdonotknowfile")){
                    printf("remove error\n");
                }
                exit(0);
            }
            break;
        }
    default:
        break;
    }

    if (backgroud == 1){
        printf("process id %d\n", pid);
        return;
    }
    if(waitpid(pid, &status, 0) == -1){
        printf("wait for pid error\n");
    }
}

