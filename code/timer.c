#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//@TODO refactor EVERYTHING


//int clock_gettime(clockid_t clk_id, struct timespec *tp);


struct itimerspec spec;
int iterations = 0;
char timeToLeave = 0;
struct timespec start;
struct timespec end;

void timer_handler (int signum){
  static int countiteration = 0;

  clock_gettime(CLOCK_REALTIME,&end);

  unsigned int timePassed = (end.tv_sec*1000000000 +  end.tv_nsec) -
  (start.tv_sec*1000000000 + start.tv_nsec);
  printf("%d\n",timePassed);

  if(++countiteration >= iterations){
    exit(0);
  }
  clock_gettime(CLOCK_REALTIME,&start);
}

int main (int argc,char **argv){

  timer_t timer;
  struct sigevent event;
  iterations = 70000;

  // Configurer le timer
  signal(SIGRTMIN, timer_handler);
  event.sigev_notify = SIGEV_SIGNAL;
  event.sigev_signo  = SIGRTMIN;
  double nsec = 1000  * 1000;// en nanosec
  spec.it_interval.tv_sec  = (int)nsec / 1000000000;
  spec.it_interval.tv_nsec = (int)nsec % 1000000000;
  spec.it_value = spec.it_interval;

  // Allouer le timer
  timer_create(CLOCK_REALTIME, &event, &timer);


  clock_gettime(CLOCK_REALTIME,&start);

  // Programmer le timer
  timer_settime(timer, 0, &spec, NULL);

  while (!timeToLeave) ;

  return 0;
}
