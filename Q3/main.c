#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>

#define STACK_SIZE (1024 * 1024)    /* Stack size for cloned child */

static char child_stack[STACK_SIZE];



static int fun_just(void *args){
    sleep(10000);
    return 0;
}
int main(){


    
    char *command="./exc_dir/cpu_heavy";
    char *argument_list[]={NULL};
    

    pid_t child_pid;
    child_pid = clone(fun_just, child_stack + STACK_SIZE,CLONE_NEWPID | SIGCHLD,"new_pid_namespace");

    char pid_no[64];
    char filename[1000];

    sprintf(pid_no,"%d",child_pid);
    sprintf(filename, "/proc/%s/ns/pid", pid_no);  

    int fd = open(filename, O_RDONLY);

    setns(fd, 0);

    int pid_curr=getpid();

    //printf("%d\n",pid_curr);
    
    
    
    /*FILE *fptr;
    
    fptr = fopen("/sys/fs/cgroup/cpu/my_group/tasks","w");
    
    if(fptr == NULL){
      printf("Error!");   
    }

    fprintf(fptr,"%d",pid_curr);
    fclose(fptr);*/

    

    


    for(int i=0;i<5;i++){

        if(fork()==0){
            execvp(command,argument_list);
            exit(1);
        }
    }
    
    
  

}
