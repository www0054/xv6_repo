#include "kernel/types.h"
#include "user.h"
int main(int argc, char* argv[]){
    int p1[2]; 
    int p2[2];
    pipe(p1);
    pipe(p2);
    int ret = fork();
    if(ret == 0) {
        /*子进程*/
        close(p1[1]);  //p[1]为管道写入端，p[0]为管道读出端
        close(p2[0]);
        char sonbuff[4];
        read(p1[0], sonbuff, 4);
        close(p1[0]);
        printf("%d: received %s\n", getpid(), sonbuff); 
        write(p2[1],"pong", 4);
        close(p2[1]);
        
    }else if(ret > 0){
        /*父进程*/
        close(p1[0]); //关闭读端
        close(p2[1]);
        write(p1[1],"ping", 4);
        close(p1[1]);
        char fatherbuff[4];
        read(p2[0],fatherbuff, 4);     
        close(p2[0]);
        printf("%d: received %s\n",getpid(), fatherbuff);
    }
    exit(0);
}