#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

sem_t nombre_de_chaises;
sem_t porte;
sem_t coiffeur;
sem_t chaise_coiffeur;
int nombre_de_chaises_auccupe=0;

void *code_coiffeur(void *args){

    while (1)
    {
        if(nombre_de_chaises_auccupe==0)
        {
            printf("Pas de clients a coiffer pour le moment\n");
            sem_post(&porte);
            printf("Le coiffeur ferme la porte\n");
            sem_wait(&coiffeur);
            printf("Le coiffeur dort\n");
        }
        else{
            sem_post(&chaise_coiffeur);
            printf("Un client  se coiffe et il y'a %d clients en salle\n",nombre_de_chaises_auccupe);
            sem_wait(&nombre_de_chaises);
            nombre_de_chaises_auccupe--;
            sem_post(&nombre_de_chaises);
        }
    }
}
void *code_client(void *args){

    while (1){
        if(nombre_de_chaises_auccupe==5)
        {
            printf("Salle pleine pour le moment\n");
            sem_wait(&porte);
        }
        else
        {
            sem_wait(&nombre_de_chaises);
            nombre_de_chaises_auccupe++;
            sem_post(&nombre_de_chaises);
            if(nombre_de_chaises_auccupe==0)
            {
                sem_post(&coiffeur);
                printf("Reveil du coiffeur\n");
            }
            sem_wait(&chaise_coiffeur);
        }
    }
}




int main(){
    pthread_t t1,t2;
    sem_init(&nombre_de_chaises,1,1);
    sem_init(&porte,1,1);
    sem_init(&coiffeur,1,1);
    sem_init(&chaise_coiffeur,1,1);
    pthread_create(&t1,NULL,code_client,NULL);
    pthread_create(&t2,NULL,code_coiffeur,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return EXIT_SUCCESS;
}