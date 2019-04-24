#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <omp.h>
#include <sys/time.h>

#define N 200

double stamp;

double getusec_() {
	struct timeval time;
	gettimeofday(&time, NULL);
	return ((double)time.tv_sec * (double)1e6 + (double)time.tv_usec);
}

#define START_COUNT_TIME stamp = getusec_();
#define STOP_COUNT_TIME(_m) stamp = getusec_() - stamp;\
				    stamp = stamp/1e6;\
				    printf ("%s: %0.6fs\n",(_m), stamp);

void setRandom(int mat[N][N])
{
	int i, j;
	for(i = 0; i < N; i++)
	{
		for( j = 0; j<N; j++)
		{
			mat[i][j] = rand()%20000;
		}
	}
}

void set(int mat[N][N], int val)
{
	int i,j;
	for( i = 0; i < N; i++)
	{
		for( j = 0; j < N; j++){
			mat[i][j] = val;
		}

	}
}

void printMat(int mat[N][N])
{
	int i, j;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			printf(" %d", mat[i][j]);
		}
		printf("\n");
	}
}

void multMat(int a[N][N], int b[N][N], int c[N][N])
{
	int i, j, k;
	for(i = 0; i<N; i++){
		for(j = 0; j<N; j++){
			#pragma omp task
			for(k = 0; k<N; k++){
				c[i][j] += a[i][k]*b[k][j];
			}
		}
	}
}

int checkMultMat(int a[N][N], int b[N][N], int c[N][N])
{
	int i, j, k;
	for(i = 0; i<N; i++){
		for(j = 0; j<N; j++){
			for(k = 0; k<N; k++){
				c[i][j] -= a[i][k]*b[k][j];
			}
			if(c[i][j]) return 0;
		}
	}
	return 1;

}

int A[N][N]; 
int B[N][N];
int C[N][N];

int main(int argc, char *argv[]) {

	setRandom(A);
	setRandom(B);
	set(C, 0);

	START_COUNT_TIME;
	#pragma omp parallel
	#ifdef GOMP 
	#pragma omp single
	#endif
	{
		multMat(A, B, C);
	}
	STOP_COUNT_TIME("Total execution time");
	if(checkMultMat(A, B, C)) printf("Correct\n");
	else printf("Failed\n");

	/* End timing  */

}
