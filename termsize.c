#define MAXLINE 50

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<termios.h>
#include<sys/ioctl.h>
#include<stdlib.h>
#include"jc_err.h"


struct winsize size;

static void sig_winch()
{
        if(ioctl(STDIN_FILENO,TIOCGWINSZ,(char *)&size)<0){              
                err_sys("[server]TIOCGWINSZ error");
        }
        printf("[size changed]\twidth:%d\theight:%d\n",size.ws_col,size.ws_row);
}
int main()
{       
        
        if(ioctl(STDIN_FILENO,TIOCGWINSZ,(char *)&size)<0){
                err_sys("[server]TIOCGWINSZ error");
        }
        if(isatty(STDIN_FILENO)==0){
                exit(1);
        }
        if((signal(SIGWINCH,sig_winch)==SIG_ERR)<0){
                err_sys("[server]TIOCGWINSZ error");
        }
        
        printf("[init size]\twidth:%d\theight:%d\n",size.ws_col,size.ws_row);

        for(;;);
        
}

