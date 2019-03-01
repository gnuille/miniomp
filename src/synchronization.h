#include <pthread.h>

// Default lock for unnamed critical sections
extern pthread_mutex_t miniomp_default_lock;

// Default barrier within a parallel region
extern pthread_barrier_t miniomp_barrier;

// Functions implemented in this module
void GOMP_critical_start (void);
void GOMP_critical_end (void);
void GOMP_critical_name_start (void **pptr);
void GOMP_critical_name_end (void **pptr);
void GOMP_barrier(void);
