#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_VALUE 100

int sharedData;
sem_t semaphore;

void *thread1(void *arg)
{
    int doubledValue;
    
    // Wait until the semaphore is available
    sem_wait(&semaphore);
    
    // Read the shared data
    doubledValue = 2 * sharedData;
    
    // Print the doubled value
    printf("Thread 1: Doubled value: %d\n", doubledValue);
    
    // Release the semaphore
    sem_post(&semaphore);
    
    pthread_exit(NULL);
}

void *thread2(void *arg)
{
    int fiveTimesValue;
    
    // Wait until the semaphore is available
    sem_wait(&semaphore);
    
    // Read the shared data
    fiveTimesValue = 5 * sharedData;
    
    // Print five times the value
    printf("Thread 2: Five times value: %d\n", fiveTimesValue);
    
    // Release the semaphore
    sem_post(&semaphore);
    
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid1, tid2;
    
    // Initialize the semaphore
    sem_init(&semaphore, 0, 1);
    
    // Read the shared data
    printf("Enter an integer value: ");
    scanf("%d", &sharedData);
    
    // Create the first thread
    if (pthread_create(&tid1, NULL, thread1, NULL) != 0)
    {
        fprintf(stderr, "Failed to create thread 1\n");
        return 1;
    }
    
    // Create the second thread
    if (pthread_create(&tid2, NULL, thread2, NULL) != 0)
    {
        fprintf(stderr, "Failed to create thread 2\n");
        return 1;
    }
    
    // Wait for the threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    // Destroy the semaphore
    sem_destroy(&semaphore);
    
    return 0;
}

