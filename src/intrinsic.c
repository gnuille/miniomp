#include "libminiomp.h"

void omp_set_num_threads (int n) {
  miniomp_icv.nthreads_var = (n > 0 ? n : 1);
}

int omp_get_num_threads (void) {
  return(miniomp_icv.nthreads_var);
}

int omp_get_thread_num (void) {
	return ((thread_data*) pthread_getspecific(miniomp_specifickey))->tid;

#if 0
  printf("TBI: omp_get_thread_num still doesn't know who I am ... let's say I am 0\n");
  return(0);
#endif

}

// No need to implement this function, it is just involked by Extrae at some point
// and returns the current nesting for parallel regions
int omp_get_level (void) {
    printf("TBI: omp_get_level ... let say current nesting level is 1\n");
    return(1);
}

