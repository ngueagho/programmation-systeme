#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

sem_t coiffeur;
sem_t nombre_de_chaises;
int nombre_de_chaises_auccupe= 0;

#define libre 1
#define occupe 0

int chaise_client[5]={libre,libre,libre,libre,libre};
int chaise_coiffeur[1]={libre};
int id = 0;

void *code_client(void *args){

    while (nombre_de_chaises_auccupe)
    {
        sleep(1);
        sem_wait(&nombre_de_chaises);
            if(nombre_de_chaises_auccupe<=4){
                id+=1;
                chaise_client[nombre_de_chaises_auccupe]=id;
                printf("clients assis a la place %d\n",nombre_de_chaises_auccupe);
                nombre_de_chaises_auccupe+=1;
                printf("nombre de places = %d\n",nombre_de_chaises_auccupe);
                    sem_wait(&coiffeur);
                    chaise_coiffeur[0]=occupe;
                    printf("un client est assis sur la chaise du coiffeur\n");
                    sleep(1);
                    sem_post(&nombre_de_chaises);
                        chaise_coiffeur[0]=libre;
                        printf("client numero %d dans le salon\n",id);
                        //sem_post(&coiffeur);
                    sem_wait(&nombre_de_chaises);
                    nombre_de_chaises_auccupe-=1;
                sem_post(&nombre_de_chaises);
            }
            else
            {
                sem_post(&nombre_de_chaises);
            }
    }
}

void *code_coiffeur(void *args){
    while (1){
        sem_wait(&nombre_de_chaises);
        if(nombre_de_chaises_auccupe !=0){
            if(chaise_coiffeur[0]=occupe)
            {
                sem_post(&coiffeur);
                printf("un client se coiffe\n");
                sleep(2);
            }
            sem_post(&nombre_de_chaises);
        }
        else{
            printf(" auccun client le coiffeur dort\n");
            sleep(2);
            sem_post(&nombre_de_chaises);
        }

    }
}

int main(){

    pthread_t t1,t2;
    sem_init(&nombre_de_chaises,1,1);
    sem_init(&coiffeur,1,1);
    pthread_create(&t1,NULL,code_client,NULL);
    pthread_create(&t2,NULL,code_coiffeur,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return EXIT_SUCCESS;
}