#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define SLEEP_TIME 6
#define LEFT (philosopherId + PHILOSOPHERS_NUMBER - 1) % PHILOSOPHERS_NUMBER
#define RIGHT (philosopherId + 1) % PHILOSOPHERS_NUMBER


// Variables 
int PHILOSOPHERS_NUMBER = 0;
int CHOPSTICKS_NUMBER = 0;
int *philosophers;
int *philosopherState;

pthread_mutex_t mutex;
pthread_t *thread;
sem_t *semaphore;


void intiData(){
    printf("Enter philospher number: ");
    scanf("%d", &PHILOSOPHERS_NUMBER);
    CHOPSTICKS_NUMBER = PHILOSOPHERS_NUMBER;
    philosophers = malloc(PHILOSOPHERS_NUMBER * sizeof(int));
    philosopherState = malloc(PHILOSOPHERS_NUMBER * sizeof(int));
    
    
    for(int i=0; i<PHILOSOPHERS_NUMBER; i++){
        philosophers[i] = i;
    }

    pthread_mutex_init(&mutex, NULL);
    thread = (pthread_t*)malloc(PHILOSOPHERS_NUMBER * sizeof(pthread_t));
    semaphore = (sem_t*)malloc(PHILOSOPHERS_NUMBER * sizeof(sem_t));
    srand(time(NULL));
}

void eat(int philosopherId){
    philosopherState[philosopherId] = EATING;
    sleep(rand()%SLEEP_TIME);
    printf("Philosopher [%d] takes fork [%d] and [%d]\n", philosopherId + 1, LEFT + 1, philosopherId + 1);
    printf("Philosopher [%d] is eating\n", philosopherId + 1);

    sem_post(&semaphore[philosopherId]);
}

void checkChopsticks(int philosopherId){

    if(
        philosopherState[philosopherId] == HUNGRY &&
        philosopherState[LEFT] != EATING &&
        philosopherState[RIGHT] != EATING 
     ){
         eat(philosopherId);
     }

}

void takeChopsticks(int philosopherId){
    pthread_mutex_lock(&mutex);
    // Set state to HUNGRY
    philosopherState[philosopherId] = HUNGRY;
    printf("Philosopher [%d] is hungry\n",philosopherId+1);
    // Check wheather neighbours are eating
    checkChopsticks(philosopherId);
    pthread_mutex_unlock(&mutex);

    // If they are eating wait
    sem_wait(&semaphore[philosopherId]);
    sleep(rand()%SLEEP_TIME);
}

void putChopstick(int philosopherId){
    pthread_mutex_lock(&mutex);
    // Set state to THINKING
    philosopherState[philosopherId] = THINKING;
    printf("Philosopher [%d] put back chopsticks [%d] and [%d]\n", philosopherId + 1, LEFT + 1, philosopherId + 1);
    printf("Philosopher [%d] is thinking\n",philosopherId + 1 );

    checkChopsticks(LEFT);
    checkChopsticks(RIGHT);

    pthread_mutex_unlock(&mutex);

}



void * philosopher(int* philosopherId){

    while(1){
        int* num = philosopherId;
        sleep(rand() % SLEEP_TIME);
        takeChopsticks(*num);
        putChopstick(*num);

    }
}

int main(){ 

    
    intiData();
   

    for (int i = 0; i < PHILOSOPHERS_NUMBER; i++)
    {
        if(pthread_create(&thread[i], NULL, philosopher, &philosophers[i]) != 0){
            perror("Can't create a thread\n");
        }
    }

    for (int i = 0; i < PHILOSOPHERS_NUMBER; i++){
        sem_init(&semaphore[i], 0, 0);
    }


    for (int i = 0; i < PHILOSOPHERS_NUMBER; i++)
    {
        if(pthread_join(thread[i], NULL) != 0){
            perror("Can't join a thread\n");
        }
    }
    
    free(thread);
    free(semaphore);
    pthread_mutex_destroy(&mutex);

    return 0;
}