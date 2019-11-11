#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NB_ITERATIONS 70000
#define TEMP_US	1000



void *handleThread(void *arg)
{
	//Variables utilitaires
	int countIterations = 0;
	int ret,policy = 0;
	

	//Variables permettant de gérer la différence de temps et le nanosleep
	struct timespec start;
	struct timespec end;
	struct timespec req,rem;

	//Assignation de la valeur pour nanosleep
	req.tv_sec = 0;
        req.tv_nsec = TEMP_US *1000;

	
	//Structure de stockage permettant de récupérer et modifier les paramètre de scheduling du thread
	struct sched_param threadParams;

	//Récupération et modifications des paramètres de scheduling du thread
	ret = pthread_getschedparam(pthread_self(),&policy,&threadParams);
	if(ret != 0){
		fprintf(stderr,"Cannot get schedulings parameter for the thread");
		return NULL;
	}
	
	threadParams.sched_priority = 99;
	policy = SCHED_FIFO;
	
	ret = pthread_setschedparam(pthread_self(),policy,&threadParams);
	if(ret != 0){
		fprintf(stderr,"Cannot set schedulings parameter for the thread");
		return NULL;
	} 

	clock_gettime(CLOCK_REALTIME,&start);

	//Boucle de gestion du temps et de l'affichage des temps
	while(countIterations < NB_ITERATIONS){
	
		ret = nanosleep(&req,&rem); 
		if(ret < 0)
		{	
			fprintf(stderr,"nanosleep call failled");
			return NULL;
		}

		clock_gettime(CLOCK_REALTIME,&end);
		unsigned int timePassed = (end.tv_sec*1000000000 +  end.tv_nsec) -
 		(start.tv_sec*1000000000 + start.tv_nsec);
  		printf("%d\n",timePassed);
		countIterations++;
		clock_gettime(CLOCK_REALTIME,&start);
		
	}	

	return 0;
	
			
		
}

int main(int argc, char **argv){

	int ret = 0;
	pthread_t pthrHautePriorite;

	//On crée un thread haute priorité
	ret = pthread_create(&pthrHautePriorite,NULL,handleThread,NULL);
	if(ret != 0){
		fprintf(stderr,"Error ! Could not create the thread.");
		return ret;
	}

	//On attend jusqu'à la fin de l'éxecution du thread
	ret = pthread_join(pthrHautePriorite,NULL);

	return ret;
}

