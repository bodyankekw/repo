#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
/* Функция my_handler – пользовательский 
   обработчик сигнала */
void my_handler(int nsig){
    switch (nsig)
    {
        case SIGINT:
            printf("got SIGINT");
            exit(0);
            break;
        case SIGQUIT:
            printf("got SIGQUIT");
            exit(0);
            break;
        default:
            break;
    }
}

int main(void){
    signal(SIGINT, my_handler);
    signal(SIGQUIT, my_handler);

    while(1);
    return 0;
}