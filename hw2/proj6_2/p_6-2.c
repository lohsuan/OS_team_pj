#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUMBER_OF_PHILOSOPHERS 5
#define LEFT (ph_num + NUMBER_OF_PHILOSOPHERS - 1) % NUMBER_OF_PHILOSOPHERS
#define RIGHT (ph_num + 1) % NUMBER_OF_PHILOSOPHERS

pthread_mutex_t mutex;
pthread_cond_t condition[NUMBER_OF_PHILOSOPHERS];

enum { THINKING,
       HUNGRY,
       EATING } state[NUMBER_OF_PHILOSOPHERS];

int phil_num[NUMBER_OF_PHILOSOPHERS];

void *dining(void *arg);
void pickup(int ph_num);
void putdown(int ph_num);
void test(int ph_num);

int main(int argc, char *argv[]) {
    pthread_t ph_thread[NUMBER_OF_PHILOSOPHERS];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        pthread_cond_init(&condition[i], NULL);
        phil_num[i] = i;
    }

    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {
        pthread_create(&ph_thread[i], NULL, dining, &phil_num[i]);
        printf("Philosopher #%d starts dining.\n", i + 1);
        sleep(1);
    }
    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
        pthread_join(ph_thread[i], NULL);

    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
        pthread_cond_destroy(&condition[i]);

    return (0);
}

void *dining(void *arg) {
    while (1) {
        int *ph_num = arg;
        sleep(2);
        pickup(*ph_num);
        putdown(*ph_num);
    }
}

void pickup(int ph_num) {
    pthread_mutex_lock(&mutex);

    printf("Philosopher #%d is HUNGRY.\n", ph_num + 1);
    state[ph_num] = HUNGRY;
    printf("Philosopher #%d trying to pick up chopsticks.\n", ph_num + 1);
    test(ph_num);
    while (state[ph_num] != EATING)
        pthread_cond_wait(&condition[ph_num], &mutex);

    pthread_mutex_unlock(&mutex);
}

void putdown(int ph_num) {
    pthread_mutex_lock(&mutex);

    printf("Philosopher #%d puts down chopsticks and returns to THINKING.\n", ph_num + 1);
    state[ph_num] = THINKING;
    printf("Philosopher #%d asks the neighbors if they are hungry.\n", ph_num + 1);
    test(LEFT);
    test(RIGHT);

    pthread_mutex_unlock(&mutex);
}

void test(int ph_num) {
    if (state[ph_num] == HUNGRY &&
        state[LEFT] != EATING &&
        state[RIGHT] != EATING) {
        printf("Philosopher #%d starts EATING.\n", ph_num + 1);
        state[ph_num] = EATING;
        sleep(3);
        pthread_cond_signal(&condition[ph_num]);
    }
}
