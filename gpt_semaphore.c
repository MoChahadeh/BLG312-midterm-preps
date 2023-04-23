#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 5

sem_t my_semaphore;

void* my_thread(void* arg) {
    int thread_num = *((int*)arg);
    printf("Thread %d started\n", thread_num);

    if (thread_num > 0) {
        sem_wait(&my_semaphore); // Wait for the previous thread to release the semaphore
        printf("Thread %d got semaphore\n", thread_num);
    }

    // Do some work with the shared resource
    sleep(5);

    if (thread_num < NUM_THREADS - 1) {
        sem_post(&my_semaphore); // Release the semaphore for the next thread
    }

    printf("Thread %d finished\n", thread_num);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_nums[NUM_THREADS];

    sem_init(&my_semaphore, 0, 1); // Initialize the semaphore with value 1

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_nums[i] = i;
        pthread_create(&threads[i], NULL, my_thread, &thread_nums[i]); // Start threads with their numbers as arguments
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); // Wait for the threads to finish
    }

    sem_destroy(&my_semaphore); // Destroy the semaphore

    return 0;
}
