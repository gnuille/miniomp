#include "libminiomp.h"

// This file implements the PARALLEL construct

// Declaration of array for storing pthread identifier from pthread_create function
pthread_t *miniomp_threads;

thread_data *miniomp_thread_data;

// Global variable for parallel descriptor
miniomp_parallel_t *miniomp_parallel;

// Declaration of per-thread specific key
pthread_key_t miniomp_specifickey;

// This is the prototype for the Pthreads starting function
void *worker(void *args) {
	// insert all necessary code here for:
	//   1) save thread-specific data
	//   2) invoke the per-threads instance of function encapsulating the parallel region
	//   3) exit the function
	return(NULL);
}

void *iddle(void *tid)
{	
	miniomp_thread_data[(int) (long) tid].tid = (int) (long) tid;
	pthread_setspecific(miniomp_specifickey, &miniomp_thread_data[(int) (long) tid]); 
//	while(1);
	printf("Worker %i creat\n", miniomp_thread_data[(int) (long) tid].tid);
	pthread_exit(NULL);
}

void *init_master(void* exec)
{
	miniomp_parallel_t* ec = exec;
	miniomp_thread_data[((miniomp_parallel_t*) exec)->id].tid = ((miniomp_parallel_t*)exec)->id;
	pthread_setspecific(miniomp_specifickey, &miniomp_thread_data[((miniomp_parallel_t*)exec)->id]);
	ec->fn(ec->fn_data);
	pthread_exit(NULL);
}
	
void
GOMP_parallel (void (*fn) (void *), void *data, unsigned num_threads, unsigned int flags) {
	if(!num_threads) num_threads = omp_get_num_threads();
	miniomp_parallel->fn = fn;
	miniomp_parallel->fn_data = data;
	miniomp_parallel->id = 0;
	pthread_create(&miniomp_threads[0], NULL, &init_master, miniomp_parallel); 
	for(int i = 1; i < num_threads; i++) 
		pthread_create(&miniomp_threads[i], NULL, &iddle, (void *)(long) i);
	for(int i = 0; i < num_threads; i++)
		pthread_join(miniomp_threads[i], NULL);



#if 0
				printf("Starting a parallel region using %d threads\n", num_threads);
				for (int i=0; i<num_threads; i++)
				fn (data);
#endif

}
