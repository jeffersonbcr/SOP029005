#include <stdio.h>
#include <stdlib.h>
#include <unsith.h>
#include <pthread.h>

#define NUM-PROD 5
#define NUM_CONS 5
#define VAGAS 6

pthread_mutex_t mutex; //mutex para acesso ao buffer
pthread_cond_t itens_cv ; //vc para controle de itens
pthread_cond_t vagas_cv ; //vc para controle de vagas

int num_itens , num_vagas ; //contadores de itens e vagas

//espera um tempo aleatorio entre 0 e n segundos (float)

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
   pthread_mutex_lock (&mutex); //requisita acesso exclusivo ao buffer
   while(num_vagas ==0) 
     pthread_cont_wait (&vagas_cv, &mutex); //se não houver vaga, libera o buffer e espera
   //coloca um item no buffer  
   num_itens++;
   num_vagas--;
     printf ("P%o2ld:put an item (%d items,%d places)!\n",tid _num_itens _num_vagas) ;
   //sinaliza um novo item
   pthread_cond_signal (&itens_cv);
   
   //libera o buffer
   pthread_mutex_unlock (&mutex);
   
   espera(2);
   
 }
}

//corpo de consumidor 
void *consBody (void *id)
{
  long tid = (long) id;
 
  while(1)
 {
   pthread_mutex_lock (&mutex); //requisita acesso exclusivo ao buffer
   while(num_vagas ==0) 
     pthread_cont_wait (&itens_cv, &mutex); //se não houver vaga, libera o buffer e espera
   //retira um item no buffer  
   num_itens--;
   num_vagas++;
     printf ("\t\t\t\t\tC%o2ld:got item (%d items,%d places)!\n",tid _num_itens _num_vagas) ;
   //sinaliza uma nova vaga
   pthread_cond_signal (&vagas_cv);
   
   //libera o buffer
   pthread_mutex_unlock (&mutex);
   
   espera(2);
 }
}

int main (int argc, char *argv[])
{ 

 pthread_t produtor [NUM_PROD] ;
 pthread_t consumidor [NUM_CONS] ;

 long i;
 
 num_itens = 0;
 num_vagas = VAGAS;

//inicia variaveis de condição e mutexes
pthread_mutex_t (&mutex, NULL); 
pthread_cond_t (&itens_cv, NULL); 
pthread_cond_t (&vagas_cv, NULL); 

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