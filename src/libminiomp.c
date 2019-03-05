#include "libminiomp.h"
//#include "intrinsic.h"

// Library constructor and desctructor
void init_miniomp(void) __attribute__((constructor));
void fini_miniomp(void) __attribute__((destructor));

// Function to parse OMP_NUM_THREADS environment variable
void parse_env(void);

void destroy_specifickey(void * arg)
{
}
int end;
void
init_miniomp(void) {
	printf ("mini-omp is being initialized\n");
	// Parse OMP_NUM_THREADS environment variable to initialize nthreads_var internal control variable
	parse_env();
	miniomp_threads = malloc(sizeof(pthread_t)*MAX_THREADS);
	miniomp_thread_data = malloc(sizeof(thread_data)*MAX_THREADS);
	miniomp_parallel = malloc(sizeof(miniomp_parallel_t));
        pthread_key_create(&miniomp_specifickey, destroy_specifickey);
	pthread_setspecific(miniomp_specifickey, &miniomp_thread_data[0]);
	miniomp_thread_data[0].tid = 0;
	end = 0;
	int i;
	for (i = 1; i<miniomp_icv.nthreads_var; i++){
		printf("Created thread %i\n", i);
		pthread_create(&miniomp_threads[i],
			NULL,
			&worker,
			(void *)(long) i);

	}
		// Initialize Pthread data structures 
		// Initialize Pthread thread-specific data, useful for example to store the OpenMP thread identifier
		// Initialize OpenMP default lock and default barrier
		// Initialize OpenMP workdescriptors for for and single 
		// Initialize OpenMP task queue for task and taskloop
}

void
fini_miniomp(void) {
	// free structures allocated during library initialization	
	pthread_key_delete(miniomp_specifickey);
	end = 1;
	free(miniomp_parallel);
	free(miniomp_thread_data);
	free(miniomp_threads);
	//right now no support for dynamic change of NTHREADS
	printf ("mini-omp is finalized\n");
}
