#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

#define MAX 100
#define BUF_SIZE 3

typedef struct args{ //args :denote l des functions systems........argc:argument constant  argv: argument vector
sem_t sem_free;
sem_t sem_busy;
}args_t;
void *prod(void *arg);
void *cons(void *arg);
static int buf[BUF_SIZE];

void *prod(void *arg){
    int ip=0, nbprod=0, obj=1001;
    args_t *args = (args_t*)arg;
    while(nbprod<MAX){
        sem_wait (&args->sem_free);
        buf[ip]=obj;
        sem_post(&args->sem_busy);
        printf("pro: buf[%d]=%d\n",ip,obj);
        obj++;
        nbprod++;
        ip=(ip+1)%BUF_SIZE;
    }
    return NULL;
}

void *cons(void *arg){
    int ic=0,nbcons=0,obj;
    args_t *args= (args_t*)arg;
    while(nbcons<MAX){
        sleep(1)  ;
        sem_wait(&args->sem_busy);
        obj=buf[ic];
        sem_post(&args->sem_free);
        printf("cons: buf[%d]=%d\n",ic,obj);
        nbcons++;
        ic=(ic+1)%BUF_SIZE;
    }
    return NULL;
}

int main(){
    int p,i;
    pthread_t t1,t2;
    args_t args;
    sem_init(&args.sem_free,0,BUF_SIZE);
    sem_init(&args.sem_busy,0,0);
    pthread_create(&t1,NULL,prod,&args);
    pthread_create(&t2,NULL,cons,&args);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("exit\n");
    return EXIT_SUCCESS;
}
