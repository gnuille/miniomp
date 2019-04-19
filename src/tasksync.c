#include "libminiomp.h"

// Called when encountering taskwait and taskgroup constructs

void
GOMP_taskwait (void)
{
	int cont=0;
	while(!is_empty(miniomp_taskqueue)){
		lock(miniomp_taskqueue);
		if( !is_empty(miniomp_taskqueue) ) {
			miniomp_task_t *t = first(miniomp_taskqueue);
			dequeue(miniomp_taskqueue);
			unlock(miniomp_taskqueue);
			t->fn(t->data);
			cont++;
		}else{
			unlock(miniomp_taskqueue);
		}

	}
	lock(miniomp_taskqueue);
	miniomp_taskqueue->finished_count -= cont;
	unlock(miniomp_taskqueue);
	while(!finished(miniomp_taskqueue)){}
}

void
GOMP_taskgroup_start (void)
{
	return;
}

void
GOMP_taskgroup_end (void)
{
	int cont=0;
	while(!is_empty(miniomp_taskqueue)){
		lock(miniomp_taskqueue);
		if( !is_empty(miniomp_taskqueue) ) {
			miniomp_task_t *t = first(miniomp_taskqueue);
			dequeue(miniomp_taskqueue);
			unlock(miniomp_taskqueue);
			t->fn(t->data);
			cont++;
		}else{
			unlock(miniomp_taskqueue);
		}

	}
	lock(miniomp_taskqueue);
	miniomp_taskqueue->finished_count -= cont;
	unlock(miniomp_taskqueue);
	while(!finished(miniomp_taskqueue)){}
}
