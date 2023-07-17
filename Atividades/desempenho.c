#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

//alterar o numero de filosofos 

#define NUMFILO 5

pthread_t filosofo [NUMFILO];
sem_t hashi [NUMFILO];
sem_t saleiro;

char *space[] = {"","\t","\t\t","\t\t\t","\t\t\t\t"};

void espera(int n){
   sleep(random()%n);
   usleep(random()%1000000);
}

void come(int f){  
   printf("%sCOMENDO\n", space[f]);
   
}


void medita (int f){
   printf("%smeditando\n", space[f]);
   
}

void pega_hashi (int f, int h){
   printf("%squer h%d\n", space[f],h);
   sem_wait(&hashi[h]);
   printf("%spegou h%d\n", space[f],h);
}

void larga_hashi(int f, int h){
   printf("%slarga h%d\n", space[f],h);
   sem_post(&hashi [h]);
}

void *threadFilosofo (void *arg){
   
   int k=0; //k controla a quantidade de vezes que quer que cada filósofo coma
   int i = (long int ) arg;
   while(1){
     medita(i);
     sem_wait(&saleiro);
     pega_hashi(i,i);
     pega_hashi(i,(i+1) % NUMFILO);
     sem_post(&saleiro);
     come(i);
     larga_hashi(i,i);
     larga_hashi(i,(i+1) % NUMFILO);
     k++;
     printf("Filosofo %d está com valor de k: %d \n",i,k);
     if(k==1000){
       printf("O filosofo %d parou de comer",i);
       break;
     }
    
   }
   pthread_exit( NULL );
}

int main (int argc, char *argv[]){
   long i, status;

   setvbuf(stdout,0, _IONBF,0);

   for(i=0;i<NUMFILO;i++)
     sem_init(&hashi[i],0,1);

   sem_init(&saleiro, 0, NUMFILO-1);
   
   for(i=0;i<NUMFILO;i++){
     status = pthread_create(&filosofo[i], NULL, threadFilosofo, (void*)i);
     if(status){
       perror ("pthread_create");
       exit(1);
     }
   }
   
   pthread_exit(NULL);
}
  



