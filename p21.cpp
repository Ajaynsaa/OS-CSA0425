#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define LEFT (phil_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (phil_id + 1) % NUM_PHILOSOPHERS
#define THINKING 0
#define HUNGRY 1
#define EATING 2

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_cond_t cond_vars[NUM_PHILOSOPHERS];
int states[NUM_PHILOSOPHERS];

int canEat(int phil_id) {
    return (states[LEFT] != EATING && states[RIGHT] != EATING);
}
//about the philosopher hungry

void pickupForks(int phil_id) {
    pthread_mutex_lock(&forks[phil_id]);
    states[phil_id] = HUNGRY;
    while (!canEat(phil_id)) {
        pthread_cond_wait(&cond_vars[phil_id], &forks[phil_id]);
    }
    states[phil_id] = EATING;
    pthread_mutex_unlock(&forks[phil_id]);
}
// calculate the pickup forks
void putdownForks(int phil_id) {
    pthread_mutex_lock(&forks[phil_id]);
    states[phil_id] = THINKING;
    if (states[LEFT] == HUNGRY && canEat(LEFT)) {
        states[LEFT] = EATING;
        pthread_cond_signal(&cond_vars[LEFT]);
    }
    if (states[RIGHT] == HUNGRY && canEat(RIGHT)) {
        states[RIGHT] = EATING;
        pthread_cond_signal(&cond_vars[RIGHT]);
    }
    pthread_mutex_unlock(&forks[phil_id]);
}
// printing the philosopher action
void* philosopherActions(void* philosopher) {
    int phil_id = *((int*)philosopher);
    while (1) {
        printf("Philosopher %d is thinking.\n", phil_id);
        sleep(1);
        printf("Philosopher %d is hungry.\n", phil_id);
        pickupForks(phil_id);
        printf("Philosopher %d is eating.\n", phil_id);
        sleep(2);
        putdownForks(phil_id);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
        pthread_cond_init(&cond_vars[i], NULL);
        states[i] = THINKING;
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopherActions, &philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
        pthread_cond_destroy(&cond_vars[i]);
    }

    return 0;
}
