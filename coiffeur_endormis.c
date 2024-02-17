#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

#define libre 0
#define occupe 1
#define N 10
#define id 0
typedef struct args{
    sem_t chaise_libre;
    sem_t chaise_coiffeur_libre;
}args_t ;
int chaise_coiffeur[1]= {libre} ;
int chaise_client[N]={libre,libre,libre,libre,libre,libre,libre,libre,libre,libre};




void *coiffeur(void *agr){
    args_t *arg=(args_t*)arg;
    while(1){
        if(chaise_coiffeur[0]==occupe){
            sem_post(&arg->chaise_coiffeur_libre);
            printf("client [] coiffe'\n");
            sem_wait(&arg->chaise_libre);

        }
    }
}

void *client(void *args){
    int max=0; int ic=0;
    args_t *arg=(args_t*)arg;
    while(max<=N){
        sleep(1);
        sem_wait(&arg->chaise_libre);
            if(chaise_client[ic]==libre){
                chaise_client[ic]=occupe;
                max ++;
                sem_post(&arg->chaise_libre);
                printf("client [%d] assis\n",ic);
                sem_wait(&arg->chaise_coiffeur_libre);
                sleep(1);
                if(chaise_coiffeur[0]==libre){
                    chaise_coiffeur[0]==occupe;
                }
            }
            else sem_post(&arg->chaise_libre);

    }
}

int main(){
    pthread_t t1,t2;
    args_t args;
    sem_init(&args.chaise_libre,0,N);
    sem_init(&args.chaise_coiffeur_libre,0,N);
    pthread_create(&t1,NULL,coiffeur,&args);
    pthread_create(&t2,NULL,client,&args);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("exit\n");
    return EXIT_SUCCESS;
}


