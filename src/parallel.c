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

void *worker(void *tid)
{	
	// insert all necessary code here for:
	//   1) save thread-specific data
	//   2) invoke the per-threads instance of function encapsulating the parallel region
	//   3) exit the function
	miniomp_thread_data[(int) (long) tid].tid = (int) (long) tid;
	pthread_setspecific(miniomp_specifickey, 
			    &miniomp_thread_data[(int) (long) tid]); 
	printf("Worker %i creat\n", 
		miniomp_thread_data[(int) (long) tid].tid);
	while(!end){
	};
	pthread_exit(NULL);
}
	
void
GOMP_parallel (void (*fn) (void *), void *data, unsigned num_threads, unsigned int flags) {
	int orig=miniomp_icv.nthreads_var;
	omp_set_num_threads(num_threads);	
	fn(data);
	omp_set_num_threads(orig);
}
