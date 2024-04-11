#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 4

int N = 100;
sem_t semaphore; // 세마포어 변수

void *thread_func(void *arg) {
    int thread_id = *(int *)arg; //스레드 아이디 지정

    int start = (N / NUM_THREADS) * thread_id + 1; // 스레드마다 시작 넘버 지정
    int end = (N / NUM_THREADS) * (thread_id + 1); // 스레드마다 끝 넘버 지정

    for (int i = start; i <= end; ++i) {
        sem_wait(&semaphore); // 세마포어 값이 양수일때까지 기다렸다가 양수이면 진입
        printf("Thread %d: %d\n", thread_id +1 ,i * 3); // critical section
        sem_post(&semaphore); // 임계 구역을 벗어나면 세마포어 값을 증가시켜 다른 스레드가 임계 구역에 진입할 수 있도록 함
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    sem_init(&semaphore, 0, 1); // 세마포어를 초기화하고 초기값은 1로 설정

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
