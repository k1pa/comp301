#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <semaphore.h>

#define N		10
#define LEFT	(i + N-1)%N
#define	RIGHT	(i + 1)%N
#define THINKING	0
#define HUNGRY		1
#define EATING		2

//semaphore
sem_t s;
sem_init(&s, 0, 1);

int main(void){
	
}

int take_forks(int i){
	//sem wait, wait until value of semaphore is greater than 0
	sem_wait(&s);
	//critical section
	
	//increment value of semaphore by 1
	sem_post(&s);
}