#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>

// Maximum number of threads to be supported by our implementation
// To be used whenever you need to dimension thread-related structures
#define MAX_THREADS 32

typedef struct{
	int tid;
	int nfunc;
}thread_data;

typedef struct{
	void (*fn) (void *);
	void *data;
}execContext;

// To implement memory barrier (flush)
//void __atomic_thread_fence(int);
#define mb() __atomic_thread_fence(3)

#include "intrinsic.h"
#include "env.h"
#include "parallel.h"
#include "synchronization.h"
#include "loop.h"
#include "single.h"
#include "task.h"
