#include "libminiomp.h"

// This file implements the PARALLEL construct

// Declaration of array for storing pthread identifier from pthread_create function
pthread_t *miniomp_threads;

thread_data *miniomp_thread_data;

// Declaration of per-thread specific key
pthread_key_t miniomp_specifickey;

extern void GOMP_taskwait(void);
extern int in_taskgroup;
extern int taskgroup_counter;
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
	int executed = 0;
	while(1){
		if( !is_empty(miniomp_taskqueue) ){
			lock(miniomp_taskqueue);
				if( !is_empty(miniomp_taskqueue) ){
					miniomp_task_t *t = first(miniomp_taskqueue);
					dequeue(miniomp_taskqueue);
					unlock(miniomp_taskqueue);
					t->fn(t->data);
					executed++;
					if(t->in_taskgroup){
						__sync_fetch_and_sub(&taskgroup_counter, 1);
					}
				}else{
					unlock(miniomp_taskqueue);
				}
		}else{
			if(executed > 0 ){
				__sync_fetch_and_sub(&miniomp_taskqueue->finished_count, executed);
				executed = 0;

			}
			

		}	
	
	}
	pthread_exit(NULL);
}
	
void
GOMP_parallel (void (*fn) (void *), void *data, unsigned num_threads, unsigned int flags) {
	int orig = 0;
	if(num_threads){
		orig = miniomp_icv.nthreads_var;
		omp_set_num_threads(num_threads);
	}
	fn(data);

	GOMP_taskwait();

	if(num_threads) omp_set_num_threads(orig);
}
