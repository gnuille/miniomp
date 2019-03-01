#include "libminiomp.h"

// Default lock for critical sections
pthread_mutex_t miniomp_default_lock;

void GOMP_critical_start (void) {
  printf("TBI: Entering an unnamed critical, don't know if anyone else is alrady in. I proceed\n");
}

void GOMP_critical_end (void) {
  printf("TBI: Exiting an unnamed critical section. I can not inform anyone else, bye!\n");
}

void GOMP_critical_name_start (void **pptr) {
  pthread_mutex_t * plock = *pptr;
  printf("TBI: Entering a named critical %p (%p), don't know if anyone else is alrady in. I proceed\n", pptr, plock);
  // if plock is NULL it means that the lock associated to the name has not yet been allocated and initialized
}

void GOMP_critical_name_end (void **pptr) {
  pthread_mutex_t * plock = *pptr;
  printf("TBI: Exiting a named critical %p (%p), I can not inform anyone else, bye!\n", pptr, plock);
  // if plock is still NULL something went wrong
}

pthread_barrier_t miniomp_barrier;

void GOMP_barrier() {
  printf("TBI: Entering in barrier, but do not know how to wait for the rest. I proceed\n");
}
