/*
	Name: Shaun Allen
	ID: 1259316
*/

#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <sched.h>

#define _GNU_SOURCE
#include <pthread.h>
#define N		10
#define LEFT	(i + N-1)%N
#define	RIGHT	(i + 1)%N
#define THINKING	0
#define EATING		1
//holds whether each philosopher is thinking or eating
int state[N] = { 0 };
//pthread array for philosophers
pthread_t philosophers[N];
//to eliminate race conditions
pthread_mutex_t mutex_forks[N];

void *philosopher(int i){
	//take forks, check to see if we can or not	state[i] = THINKING;
	printf("philosopher %d is thinking.....\n", i);
	sched_yield();
	
	pthread_mutex_lock(&mutex_forks[LEFT]);
	sched_yield();
	//sleep(1000);
	pthread_mutex_lock(&mutex_forks[RIGHT]);
	printf("philosopher %d is eating :]\n", i);
	pthread_mutex_unlock(&mutex_forks[LEFT]);
	sched_yield();
	pthread_mutex_unlock(&mutex_forks[RIGHT]);
	printf("philosopher %d has finished eating\n", i);
	return NULL;
}

int main(void){
	printf("10 philosophers at a table......\n");
	for(int i = 0; i < N; i++){
		pthread_create(&(philosophers[i]),NULL,(void *)philosopher, (void *)(intptr_t) i);
	}
	for(int i = 0; i < N; i++){
		pthread_join(philosophers[i],NULL);
	}
	printf("finished\n");
	return 0;
}