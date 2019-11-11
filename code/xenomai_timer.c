#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <native/task.h>
#include <native/timer.h>

#define NB_ITERATIONS 70000

//Basé sur : https://xenomai.org/documentation/xenomai-2.6/html/api/trivial-periodic_8c-example.html

RT_TASK periodic_task;

void periodicTimer(void *arg)
{
        int counter= 70000;
	int ret = 0;
	RTIME now, previous;
        /*
         * Arguments: &task (NULL=self),
         *            start time,
         *            period (here: 1 s)
         */
        ret = rt_task_set_periodic(NULL, TM_NOW, 1000000L);
        
	if(ret != 0){
		rt_printf("Hi");
	}

	previous = rt_timer_read();
        
	while (counter--) {
        
	        ret = rt_task_wait_period(NULL);
        
		if(ret != 0){
			rt_printf("hiHi");
		}	
	
	        now = rt_timer_read();
        
	        /*
                 * NOTE: printf may have unexpected impact on the timing of
                 *       your program. It is used here in the critical loop
                 *       only for demonstration purposes.
                 */
        
	        rt_printf("%ld\n",(now - previous));
                previous = now;
		counter++;
        }
	exit(0);
}



int main(int argc, char* argv[])
{
	//Permet d'utiliser la fonction rt_printf
	rt_print_auto_init(1);
	int ret = 0;
	

        //Permet d'eviter les mecanisme de swaping mémoire pour ce processus 
        ret = mlockall(MCL_CURRENT|MCL_FUTURE);
 
	if(ret != 0){
		rt_printf("hihihi");
	}

       /*
         * Arguments: &task,
         *            name,
         *            stack size (0=default),
         *            priority,
         *            mode (FPU, start suspended, ...)
         */
        ret = rt_task_create(&periodic_task, "XenomaiPeriodicTimer", 0, 99, 0);


	if(ret != 0){
		rt_printf("hihihihi");
		return;
	}

        /*
         * Arguments: &task,
         *            task function,
         *            function argument
         */
        ret = rt_task_start(&periodic_task, &periodicTimer, NULL);
       
	if(ret != 0){

		rt_printf("hihihihihi");
		return;
	}


	pause();

	rt_task_join(&periodic_task);
       
	rt_task_delete(&periodic_task);
        
	rt_printf("BYE");
	return 0;
}

