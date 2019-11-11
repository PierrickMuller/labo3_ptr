#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N_SEC   3
#define POWDIV  4.32

//declaration des fonctions
void comptNbIter();
void comptNpOperPow();
void comptNpOperDiv();
//Declaration des variables
time_t start_time;
time_t temp_time;
unsigned int nb_iterations;
unsigned int nb_iterations_sec;
unsigned int nb_sec_iter;
float testVal;

int main(void)
{
    printf("---Nb Iteration vides---\n");
    comptNbIter();
    printf("---Nb iteration pow---\n");
    comptNpOperPow();
    printf("---Nb iteration div---\n");
    comptNpOperDiv();
    return EXIT_SUCCESS;
}


void comptNbIter()
{
  //initialisation
  nb_sec_iter = 1;
  nb_iterations = 0;
  nb_iterations_sec = 0;
  start_time = time(NULL);
  temp_time = start_time;

  while(time(NULL) < (start_time + N_SEC)) {
    //Pour affichage toutes les secondes
    if(temp_time + 1 <= time(NULL))
    {
      temp_time = time(NULL);
      printf("nb iterations sec %d : 0x%x \n",nb_sec_iter++,nb_iterations_sec);
      nb_iterations += nb_iterations_sec;
      nb_iterations_sec = 0;
    }

    ++nb_iterations_sec;
  }

  //On s'assure qu'on a bien ajouter le nombre d'iterations de la dernière seconde
  if(nb_sec_iter == N_SEC)
  {
    nb_iterations_sec = 0;
  }
  printf("nb iterations tot (hex): 0x%x \n", nb_iterations);
}

void comptNpOperPow()
{
  //initialisation
  nb_sec_iter = 1;
  nb_iterations = 0;
  nb_iterations_sec = 0;
  start_time = time(NULL);
  temp_time = start_time;
  testVal = 1.23;

  while(time(NULL) < (start_time + N_SEC)) {
    //Pour affichage toutes les secondes
    if(temp_time + 1 <= time(NULL))
    {
      temp_time = time(NULL);
      printf("nb iterations sec %d : 0x%x \n",nb_sec_iter++,nb_iterations_sec);
      nb_iterations += nb_iterations_sec;
      nb_iterations_sec = 0;
    }
    testVal *= POWDIV;
    ++nb_iterations_sec;
  }

  //On s'assure qu'on a bien ajouter le nombre d'iterations de la dernière seconde
  if(nb_sec_iter == N_SEC)
  {
    nb_iterations_sec = 0;
  }
  printf("nb iterations tot (hex): 0x%x \n", nb_iterations);
}

void comptNpOperDiv()
{
  //initialisation
  nb_sec_iter = 1;
  nb_iterations = 0;
  nb_iterations_sec = 0;
  start_time = time(NULL);
  temp_time = start_time;
  testVal = 1.23;

  while(time(NULL) < (start_time + N_SEC)) {
    //Pour affichage toutes les secondes
    if(temp_time + 1 <= time(NULL))
    {
      temp_time = time(NULL);
      printf("nb iterations sec %d : 0x%x \n",nb_sec_iter++,nb_iterations_sec);
      nb_iterations += nb_iterations_sec;
      nb_iterations_sec = 0;
    }
    testVal /= POWDIV;
    ++nb_iterations_sec;
  }

  //On s'assure qu'on a bien ajouter le nombre d'iterations de la dernière seconde
  if(nb_sec_iter == N_SEC)
  {
    nb_iterations_sec = 0;
  }
  printf("nb iterations tot (hex): 0x%x \n", nb_iterations);
}
