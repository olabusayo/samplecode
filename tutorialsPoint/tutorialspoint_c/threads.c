#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 3

/* This is our thread function.  It is like main(), but for a thread */
void threadFunc(void *threadId)
{
	unsigned long num, modNum = NUM_THREADS * 100;
	int i = 0;

	num= *((pthread_t*)threadId);

	while(i < 10 )
	{
		usleep(1);
		printf("threadFunc says %d for %ld\n", i,(num % modNum));
		++i;
	}

}

int main(void)
{
	pthread_t pth[NUM_THREADS];	// this is our  array of thread identifiers
	int i = 0, retval = 0;

   for( i = 0; i < NUM_THREADS; i++) {

       /* Create worker thread */
       if( (retval = pthread_create(&pth[i],NULL, (void*) &threadFunc, &pth[i]))
               != 0 ) {
           fprintf(stderr, "pthread_create: %s\n", strerror(retval));
           exit(EXIT_FAILURE);
       }
   }

   for (i = 0; i < 10 ; i++ )
   {
      usleep(1);
      printf("main(%d) is running...\n", i);
   }

   for(i = 0; i < NUM_THREADS; i++) {
       /* wait for our thread to finish before continuing */
       if( (retval = pthread_join(pth[i], NULL)) != 0 ) {
           fprintf(stderr, "pthread_join: %s\n", strerror(retval));
           exit(EXIT_FAILURE);
       }
   }


	return 0;
}
