#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 3

int buffer[BUFFER_SIZE];
int count = 0;
int in = 0;
int out = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER;

void *producer(void *param);
void *consumer(void *param);

int main(int argc, char *argv[]) {
  pthread_t tid1, tid2;

  if (pthread_create(&tid1, NULL, producer, NULL) != 0) {
    fprintf(stderr, "Error creating producer thread\n");
    exit(1);
  }

  if (pthread_create(&tid2, NULL, consumer, NULL) != 0) {
    fprintf(stderr, "Error creating consumer thread\n");
    exit(1);
  }

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  return 0;
}

void *producer(void *param) {
  int data = 1;

  while (1) {
    pthread_mutex_lock(&mutex);

    while (count == BUFFER_SIZE) {
      pthread_cond_wait(&buffer_not_full, &mutex);
    }

    buffer[in] = data;
    printf("Produced item %d at position %d\n", data, in);
    in = (in + 1) % BUFFER_SIZE;
    count++;

    if (count == 1) {
      pthread_cond_broadcast(&buffer_not_empty);
    }

    if (count == BUFFER_SIZE) {
      printf("Buffer is FULL\n");
    }

    pthread_mutex_unlock(&mutex);

    data++;
    sleep(1);
  }
}

void *consumer(void *param) {
  while (1) {
    pthread_mutex_lock(&mutex);

    while (count == 0) {
      printf("Buffer is EMPTY\n");
      pthread_cond_wait(&buffer_not_empty, &mutex);
    }

    int data = buffer[out];
    printf("Consumed item %d from position %d\n", data, out);
    out = (out + 1) % BUFFER_SIZE;
    count--;

    if (count == BUFFER_SIZE - 1) {
      pthread_cond_broadcast(&buffer_not_full);
    }

    pthread_mutex_unlock(&mutex);

    sleep(2);
  }
}
