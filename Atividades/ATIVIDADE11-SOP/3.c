#include <stdio.h>
#include <stdlib.h>
#include <unsith.h>
#include <pthread.h>

#define NUM-PROD 5
#define NUM_CONS 5
#define VAGAS 6

sem_t vagas , itens; //semáforos para controle de vagas e peças 
semt_buffer ; //mutex para acesso ao buffer

int num_intes, num_vagas; //contados de vagas e peças

//espera um tempo aleatório entre 0 e n segundos (float)
void espera (int n)
{
   sleep (random() %n); // pausa entre 0 e n segundos (inteiro)
   usleep (random() %1000000); // pausa entre 0 e 1 segundos (float)	
}

//corpo de produtor 

void *prodBody (void *id)
{
  long tid = (long) id ;

  printf ("P%o2ld: Olá!\n" , tid);

 while(1)
 {
   sem_wait (&vagas);
   sem_wait (&buffer); 
   num_itens++;
   num_vagas--;
     printf ("P%o2ld:put an item (%d itens,%d vagas)!\n",tid _num_itens _num_vagas) ;
     sem_post (&buffer) ;
     sem_post (&itens) ;
     espera(2);
 }
}

//corpo de consumidor 
void *consBody (void *id)
{
  long tid = (long) id;
  printf ("C%o2ld: Olá!\n" , tid);

  while(1)
 {
   sem_wait (&itens);
   sem_wait (&buffer); 
   num_itens--;
   num_vagas++;
     printf ("C%o2ld:put an item (%d itens,%d vagas)!\n",tid _num_itens _num_vagas) ;
     sem_post (&buffer) ;
     sem_post (&vagas) ;
     espera(2);
 }
}

//programa principal

int main (int argc, char *argv[])
{ 

 pthread_t produtor [NUM_PROD] ;
 pthread_t consumidor [NUM_CONS] ;

 long i;
 
 num_itens = 0;
 num_vagas = VAGAS;

//inicia semaforos
 sem_init (&buffer, 0 , 1);
 sem_init (&vagas, 0 , VAGAS);
 sem_init (&itens, 0 , 0);

//cria produtores

for (i=0; i<NUM_PROD; i++)
 if(pthread_creat(&produtor[i] , NULL , prodBody, (void *) i))
  {
    perror ("pthread_create");
    exit(1);
  }

//cria consumidores

for (i=0; i<NUM_CONS; i++)
 if(pthread_creat(&consumidor[i] , NULL , consBody, (void *) i))
  {
    perror ("pthread_create");
    exit(1);
  }

pthread_exit (NULL);
}