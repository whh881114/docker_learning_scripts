//
// Created by Roy Wong on 2019/6/9.
//

#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024)


static char child_stack[STACK_SIZE];
char* const child_args[] = { "/bin/bash", NULL};

int child_main(void* args)
{
    printf("我们此时在子进程中！输入'exit'命令可以退出子进程，此时主机名已修改。\n");
    sethostname("NewNamespace", 12);
    execv(child_args[0], child_args);
    return 1;
}

int main()
{
    printf("程序开始：\n");
    printf("使用clone()来创建一个独立的namespace的进程，此时会进入子进程中。\n");
    printf("此时演示的是IPC namespace功能。\n");
    int child_pid = clone(child_main, child_stack + STACK_SIZE, CLONE_NEWPID | CLONE_NEWIPC | CLONE_NEWUTS | SIGCHLD, NULL);
    waitpid(child_pid, NULL, 0);
    printf("已退出子进程。\n");
    return 0;
}