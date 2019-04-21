#include "libminiomp.h"

// Called when encountering taskwait and taskgroup constructs
int in_taskgroup;
int taskgroup_counter;
pthread_mutex_t taskgroup_lock;

void
GOMP_taskwait (void)
{
	int cont=0;
	while(!is_empty(miniomp_taskqueue)){
		lock(miniomp_taskqueue);
		if(!is_empty(miniomp_taskqueue)){
			miniomp_task_t *t = first(miniomp_taskqueue);
			dequeue(miniomp_taskqueue);
			unlock(miniomp_taskqueue);
			t->fn(t->data);
			cont++;
			if(t->in_taskgroup){
				__sync_fetch_and_sub(&taskgroup_counter,1);
			}
		}else{
			unlock(miniomp_taskqueue);
		}

	}
	__sync_fetch_and_sub(&miniomp_taskqueue->finished_count, cont);
	while(1){
		mb();
		if(!miniomp_taskqueue->finished_count){
			return;
		}
	}
}

void
GOMP_taskgroup_start (void)
{
	in_taskgroup=1;
	taskgroup_counter=0;
}

void
GOMP_taskgroup_end (void)
{
	int cont = 0;
	while(taskgroup_counter > 0){
		lock(miniomp_taskqueue);
		if(!is_empty(miniomp_taskqueue)){
			miniomp_task_t *t = first(miniomp_taskqueue);
			dequeue(miniomp_taskqueue);
			unlock(miniomp_taskqueue);
			t->fn(t->data);
			cont++;
			if(t->in_taskgroup){
				__sync_fetch_and_sub(&taskgroup_counter,1);
			}
		}else{
			unlock(miniomp_taskqueue);
		}
		mb();
		
	}
	__sync_fetch_and_sub(&miniomp_taskqueue->finished_count, cont);
	while(1){
		mb();
		if(!taskgroup_counter){
			in_taskgroup=0;
			return;	
		}
	}
}
