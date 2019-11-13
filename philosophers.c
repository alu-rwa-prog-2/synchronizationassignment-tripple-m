#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// define number of philosophers
#define N 5

// defining the philosopher states
#define THINKING 2
#define HUNGRY 0
#define EATING 1
#define LEFT (philosopherNumber + 4) % N
#define RIGHT (philosopherNumber + 1) % N

// array that stores the states
int state[N];

// array that stores the philosopher numbers
int philosophers[N] = { 0, 1, 2, 3, 4 };

sem_t mutex;
sem_t synchronize[N];

void simulation (int philosopherNumber){

    if (state[philosopherNumber] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {

        // then allow the philosopher to eat if he has both chopsticks
        state[philosopherNumber] = EATING;

        // delay the simulation for 2 seconds so we can see what is happening
        sleep(2);


        printf("Philosopher %d picks fork %d and %d\n------------------------------\n",
               philosopherNumber + 1, LEFT + 1, philosopherNumber + 1);

        printf("Philosopher %d is Eating\n------------------------------\n", philosopherNumber + 1);

        // triggers hungry philosophers when another philosopher puts down the fork
        sem_post(&synchronize[philosopherNumber]);
    }
}

// pick up chopsticks
void pickFork(int philosopherNumber)
{

    sem_wait(&mutex);

    // state that hungry
    state[philosopherNumber] = HUNGRY;

    printf("Philosopher %d is Hungry\n", philosopherNumber + 1);

    // allow to eat if the neighbours are not in eating state
    simulation(philosopherNumber);

    sem_post(&mutex);

    // if unable to eat wait to be signalled
    sem_wait(&synchronize[philosopherNumber]);

    sleep(2);
}

// put down chopsticks
void putDownChopsticks (int philosopherNumber)
{

    sem_wait(&mutex);

    // state that thinking
    state[philosopherNumber] = THINKING;

    printf("Philosopher %d puts fork %d and %d down\n", philosopherNumber + 1, LEFT + 1, philosopherNumber + 1);

    printf("Philosopher %d is thinking\n", philosopherNumber + 1);

    simulation(LEFT);
    simulation(RIGHT);

    sem_post(&mutex);
}

// create philosopher threads
void* thePhilosopher (void* num){

    while (1) {

        int* x = num;

        sleep(1);

        pickFork (* x);

        sleep(1);

        putDownChopsticks (*x);
    }
}


int main() {
    int i;
    pthread_t thread_id[N];

    // initialize
    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++)

        sem_init(&synchronize [i], 0, 0);

    for (i = 0; i < N; i++) {

        // create the processes for philosophers
        pthread_create(&thread_id [i], NULL, thePhilosopher, &philosophers [i]);

        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < N; i++) { //

        pthread_join(thread_id[i], NULL);
    }
}
