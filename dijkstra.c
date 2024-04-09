#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

int flag[NUM_THREADS] = {0}; // 스레드의 임계 영역 진입 의사 표현
int turn = 0; // 순서를 결정하는 변수
int number = 1; // 숫자 초기값
int N = 100;

// 각 스레드가 실행할 함수
void *thread_func(void *arg) {
    int thread_id = *((int *)arg);
    int start = thread_id * (N / NUM_THREADS) + 1;
    int end = start + (N / NUM_THREADS) - 1;

    // 임계 영역 진입 의사 표현
    flag[thread_id] = 1;

    // 다른 스레드가 진입하고 있는 동안 기다림
    for (int other = 0; other < NUM_THREADS; other++) {
        if (other == thread_id) continue;
        while (flag[other] == 1 && turn != thread_id);
    }

    // 임계 영역 진입
    for (int i = start; i <= end; ++i) {
        printf("Thread %d: %d\n", thread_id + 1, i * 3);
    }

    // 임계 영역을 벗어나고 다음 스레드에게 차례를 넘김
    flag[thread_id] = 0;
    turn = (turn + 1) % NUM_THREADS;

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // 각 스레드 생성 및 실행
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    // 모든 스레드가 종료될 때까지 대기
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

