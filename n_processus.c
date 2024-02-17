#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
    int nombre;
    int i;
    pid_t pid;
    printf("coucou %d\n",getpid());
    // printf("mon pere s'appele %d\n",getppid());
    // fork();
    // printf("je m'apelle %d mon pere s'appele %d\n",getpid(),getppid());
    printf("entrer le nombre de processus a creer\n");
    scanf("%d",&nombre);
    for(i=1;i<=nombre;i++){
        pid=fork();
        sleep(1);
        if(pid<=-1){
            printf("echec de la creation du processus fils nomero[%d]\n",i);
            exit(EXIT_FAILURE);
        }
        else if(pid==0){
            printf("je suis le processus fils nomero[%d] de pid[%d] et la valeur aleatoire est [%d]\n",i,getpid(),rand()%100);
            exit(EXIT_SUCCESS);
        }
        else{
            printf("je suis le pere, pid[%d]\n",getpid());
            wait(NULL);
        }
    }
    exit(EXIT_SUCCESS);
    //return 0;
}
