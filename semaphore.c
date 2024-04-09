#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 4

int N = 100;
int n = 1;
sem_t semaphore; // 세마포어를 사용하여 상호 배제를 달성하는 변수

void *thread_func(void *arg) {
    int thread_id = *(int *)arg;

    int start = (N / NUM_THREADS) * thread_id + 1;
    int end = (N / NUM_THREADS) * (thread_id + 1);

    for (int i = start; i <= end; ++i) {
        sem_wait(&semaphore); // 임계 구역 진입 전에 세마포어 값이 양수인지 확인
        // critical section
        printf("Thread %d: %d\n", thread_id +1 ,i * 3);
        sem_post(&semaphore); // 임계 구역을 벗어나면 세마포어 값을 증가시켜 다른 스레드가 임계 구역에 진입할 수 있도록 함
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    sem_init(&semaphore, 0, 1); // 세마포어 초기화

    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }
    
    sem_destroy(&semaphore); // 세마포어 해제

    return 0;
}
