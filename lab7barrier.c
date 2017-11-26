//THE CODE BELOW CREATES N THREADS AND A BARRIER USING MUTEX("MUTUALLY EXCLUSIVE SEGMENT OF CODE-ONLY ONE THREAD AT A TIME CAN USE") AND A SEMAPHORE 
//A SEMAPHORE IS A MUTEX THAT REMEMBERS THE NUMBER OF THREADS THAT GET BY 
//WAIT - SEMAPHORE DECREASES WITH 1
//POST - SEMAPHORE INCREASES WITH 1

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>   
#include <sys/mman.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#define NRTHRDS 45
pthread_mutex_t mtx;
sem_t sem;
int S=0, count = 0;

void barrier_point(){
	pthread_mutex_lock(&mtx);
	count++;
	pthread_mutex_unlock(&mtx); 
	if(count < NRTHRDS){
		sem_wait(&sem); 
	}
	if(count == NRTHRDS){
		sem_post(&sem);
	}
}

void* fct_ptr_thr(void *v){
	int tid = *(int*)v;
	printf("%d reached the barrier \n", tid);
	barrier_point();
	printf("%d passed the barrier \n", tid);
}

int main(){
	int i;
	printf("NRTHRDS=%d\n", NRTHRDS);
	pthread_t pthr[NRTHRDS];
	if( pthread_mutex_init(&mtx, NULL)){
		perror(NULL);
		return errno;
	}
	if( sem_init(&sem, 0, S)){
		perror(NULL);
		return errno;
	} 
	int x[NRTHRDS];
	for( i=0; i < NRTHRDS; i++){
		x[i] = i;
	}
	for( i=0; i < NRTHRDS; i++){
		pthread_create(&pthr[i], NULL, fct_ptr_thr, &x[i]);
	}
	for( i=0; i < NRTHRDS; i++){
		pthread_join(pthr[i], NULL);
	}
	pthread_mutex_destroy(&mtx);
	sem_destroy(&sem);
	return 0;
}