#include <stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>


int pizzaNumber = 0;
int MaxTrayCapacity = 5;
int threads = 2;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * pizzaProblem (void *arg) {

    for (;;) {

        if (pizzaNumber < MaxTrayCapacity) {

            pthread_mutex_lock(&mutex);

            // we should have the chef cook more
            pizzaNumber++;

            // notify that chef cooked one more
            printf("Chef Cooked 1 more Pizza, remaining: %d\n------------------------------\n\n", pizzaNumber);

            pthread_mutex_unlock(&mutex);

            sleep(2);
        } else if (pizzaNumber == MaxTrayCapacity) {

            // notify that tray is full
            printf("Tray is Full, cannot produce, , remaining: %d\n------------------------------\n\n", pizzaNumber);

            sleep(2);
        }


        if (pizzaNumber >= 1) {

            pthread_mutex_lock(&mutex);

            // the client can remove one pizza at a time and eat
            pizzaNumber--;

            // notify that the client ate one pizza
            printf("Client ate one Pizza, remaining: %d\n------------------------------\n\n", pizzaNumber);

            pthread_mutex_unlock(&mutex);

            sleep(2);
        } else if (pizzaNumber == 0) {

            printf("Tray empty, wait for chef to cook more Pizza!, remaining: %d\n------------------------------\n\n",
                   pizzaNumber);

            sleep(2);

        }
    }
}


int main() {
    int i = 0;

    pthread_t *thread_group = malloc(sizeof(pthread_t) * threads); //create a thread group the size of THREADS

    for (i=0; i<threads; ++i)
    {
        pthread_create(&thread_group[i], NULL, pizzaProblem, NULL); //Start all threads to begin work
    }

    for (i=0; i<threads; ++i)
    {
        pthread_join(thread_group[i], NULL); // wait for all threads to finish
    }
    return EXIT_SUCCESS;
}
