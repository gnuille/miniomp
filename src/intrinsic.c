#include "libminiomp.h"

void omp_set_num_threads (int n) {
	n = (n > 0 ? n : 1);
	printf("Setting threads to %i\n", n);
	printf("iashdash\n");
	int i;
	if(n > miniomp_icv.nthreads_var){
		for(i = miniomp_icv.nthreads_var; i < n; i++){
			pthread_create(&miniomp_threads[i],
						   NULL,
						   &worker,
						   (void *)(long) i);
		}
	}else if(n < miniomp_icv.nthreads_var){
		for(i = miniomp_icv.nthreads_var -1; i>=n; i--){
			pthread_cancel(miniomp_threads[i]);
		}	
	}
	miniomp_icv.nthreads_var = n;
	printf("setted threads\n");
}

int omp_get_num_threads (void) {
	return(miniomp_icv.nthreads_var);
}

int omp_get_thread_num (void) {
	printf("getting thread num");
	return ((thread_data*) pthread_getspecific(miniomp_specifickey))->tid;
}

// No need to implement this function, it is just involked by Extrae at some point
// and returns the current nesting for parallel regions
int omp_get_level (void) {
	printf("TBI: omp_get_level ... let say current nesting level is 1\n");
	return(1);
}

