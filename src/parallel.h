#include <pthread.h>

// Declaration of array for storing pthread identifiers from pthread_create function
extern pthread_t *miniomp_threads;
extern thread_data *miniomp_thread_data;
// Declaration of per-thread specific key
extern pthread_key_t miniomp_specifickey;

// Functions implemented in this module
void GOMP_parallel (void (*fn) (void *), void *data, unsigned num_threads, unsigned int flags);

void *worker(void *tid);
