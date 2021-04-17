#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

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
   
    mvprintw(philosopherId*2, 40, "Takes chopsticks [%d] and [%d]",  LEFT + 1, philosopherId + 1);
    mvprintw(philosopherId*2, 20, "PREPARE TO EATING");
    refresh();
    sleep(3);
    move(philosopherId*2,20);
    clrtoeol();
    mvprintw(philosopherId*2, 20, "EATING");
    refresh();

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
    move(philosopherId*2,20);
    clrtoeol();
    mvprintw(philosopherId*2, 20, "HUNGRY");
    refresh();
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
  
    mvprintw(philosopherId*2, 20, "FINISH EATING");
    mvprintw(philosopherId*2, 40, "Put back chopsticks [%d] and [%d]\n", LEFT + 1, philosopherId + 1);
    refresh();
    sleep(3);
    move(philosopherId*2,20);
    clrtoeol();
    mvprintw(philosopherId*2, 20, "THINKING");
    refresh();

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
    initscr();			/* Start curses mode 		  */
	
    for(int i=0 ; i< PHILOSOPHERS_NUMBER; i++){
        mvprintw(i*2,0,"Philosopher [%d]", i+1);
    }
	
    

   

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

    getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

    return 0;
}