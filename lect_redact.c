#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
    int db =42;
    int nbl =0;
    sem_t mutex;
    sem_t redact;
void *lecteur(void *args){
        while(1){
            sem_wait(&mutex);
                if (nbl ==0)
                    sem_wait(&redact);
                    nbl++;
                    sem_post(&mutex);
                //lecture de la base
                sleep(1);
                printf("lecteur db=%d\n ", db);
                //fin de l'access a la base
                }
                sem_wait(&mutex);
                nbl-- ;
                if (nbl==0)
                    sem_post(&redact);
            sem_post(&mutex);
}

void *redacteur(void *arg){
    while(1){
        sem_wait(&redact);
        //modifier les donnes de la base
            db++;
            printf("j'ai modifie la valeur redacteur db=%d\n",db-1);
            sleep(2);//pour li demander de dormir pendant 2 secondes;
        sem_post(&redact);
    }
}

int main(){
    pthread_t t1,t2;
    sem_init(&mutex,1,1);
    sem_init(&redact,1,1);
    pthread_create(&t1,NULL,lecteur,NULL);//permet de creer un thread qui va executer la fonction lecteur;
    pthread_create(&t2,NULL,redacteur,NULL);//permet de creer un thread qui va executer la fonction redacteur;
    pthread_join(t1,NULL);
    //pthread_cancel() permet de mettre fin a un thread;
    pthread_join(t2,NULL);//comme main esst aussi un threads et comme son execution met fin a celui des autres threads,om met pthreads_join pour que main attende que les autres threads aient fini avant que le main ne face return 0;
    printf("exit\n");
    return EXIT_SUCCESS;
}