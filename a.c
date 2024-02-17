#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define N 9    //nombre de philosophes
#define G (i+1)%N   //fouchette gauche du philophe
#define D i           //fouchette droite du philophe
#define libre 1
#define occupe 0

int fourch[N]={libre,libre,libre,libre,libre,libre,libre,libre,libre};
sem_t mutex;

void *philosophe(void* num){
    int i=*(int*)num,nb=2;

    while(nb){
        sleep(1);   //penser
        sem_wait(&mutex); //  essayer de prendre les fouchettes pour manger
        if(fourch[G] == libre && fourch[D] ==libre){
            fourch[D] =occupe;
            fourch[G] =occupe;
            sem_post(&mutex);
            nb--;
            printf("philosophe[%d] mange\n",i);
            sleep(1);
            printf("philosophe[%d] a fini de manger\n",i);
            sem_wait(&mutex); //liberer les fouchettes 4
            fourch[G] =libre;
            fourch[D] =libre;
            sem_post(&mutex);
        }else sem_post(&mutex);
    }
}

int main(){
    int i,NumPhi[N]={0,1,2,3,4,5,6,7,8};
    pthread_t th[N];
    sem_init(&mutex,0,1);
    //creation des N philosophes;
    for(i=0;i<N;i++)
        pthread_create(&th[i],NULL,philosophe,&NumPhi[i]);
    //attendre la fin des threads
    for(i=0;i<N;i++)
        pthread_join(th[i],NULL);
        printf("fin des threads \n");

    return 0;
}