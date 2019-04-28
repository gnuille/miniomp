#include <stdio.h>
#include <stdlib.h>
#include <omp.h>	/* OpenMP */

int vec[(1 << 10)];
int oth[(1 <<  9)];


void assert(int val)
{
	int i;
	for( i = 0; i < (1 << 10); i++){
		if(vec[i] != val){
			printf("Assertion all values eq %d not acomplished!\n", val);
			printf("At position %d found value %d\n", i, vec[i]);
			return;
		}
	}
	printf("Assertion for value %d acomplished\n", val);
}
void assert_other(int val)
{
	int i;
	for( i = 0; i < (1 << 9); i++){
		if(oth[i] != val){
			printf("Assertion all values eq %d not acomplished!\n", val);
			printf("At position %d found value %d\n", i, oth[i]);
			return;
		}
	}
	printf("Assertion for value %d acomplished\n", val);
}

void set(int pos, int val)
{
	vec[pos] = val;
} 

void set_other(int pos, int val)
{
	oth[pos] = val;
}

void compute_low(int pos)
{
	int i;
	for ( i = 0; i<1000; i++){
		vec[pos] += i;
	}
	
	while(vec[pos] > i) vec[pos] /=2;
	int tmp = vec[pos]*4;
	while(vec[pos] < tmp) vec[pos]++;
}


void compute_other(int pos)
{
	int i;
	for ( i = 0; i<1000; i++){
		oth[pos] += i;
	}
	
	while(oth[pos] > i) oth[pos] /=2;
	int tmp = oth[pos]*4;
	while(oth[pos] < tmp) oth[pos]++;
}

void compute_high(int pos)
{
	int i;
	for ( i = 0; i<1000; i++){
		compute_low(pos);
	}

	while( i > vec[pos]) vec[pos] = (vec[pos]*21)/19;
	while( i < vec[pos]){ i = (i*21)/19; vec[pos] = (vec[pos]*21)/20;}
}

void add(int pos, int val){
	vec[pos] += val;
}
int main(int argc, char *argv[]) {
	int i, j;
	#pragma omp parallel 
	#ifdef GOMP
	#pragma omp single
	#endif
	{
		for( i = 0; i < (1 << 10); i++){
			#pragma omp task firstprivate(i)
			set(i, 1);
		}
		for( j = 0; j < (1 << 9); j++){
			#pragma omp task firstprivate(j)
			set_other(j, 1);
		}


		#pragma omp taskwait
		assert(1);
		assert_other(1);

// TASKWAIT TEST
		for( i = 0; i < (1 << 10); i++){
			#pragma omp task firstprivate(i)
			compute_low(i);
		}
		#pragma omp taskwait
		assert(3900);
//TASKGROUP TEST
		#pragma omp taskgroup
		{
		for( i = 0; i < (1 << 10); i++){
			#pragma omp task firstprivate(i)
			compute_high(i); 
		}
		}
		assert(14649);
//BIG TASK AND THEN TASKGROUP TO CHECK RUNTIME DOESNT WAIT FOR OTHER TASKS
		#pragma omp task 
		for( i = 0; i < (1 << 10); i++){
			add(i, -10000);
			compute_high(i);
			add(i, 10000);
			compute_high(i);
			add(i, -10000);
		}
		#pragma omp taskgroup
		for(j = 0; j < (1 << 9); j++){
			#pragma omp task firstprivate(j)
			compute_other(j);
		}
//THIS SHALL FAILL, PROFF OF TASKGROUP JUST WAITS FOR TASKGROUP TASKS
		assert(14649);
//THIS SHALL NOT FAILL
		assert_other(3900);
	}
}
