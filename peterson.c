#include <stdio.h>
#include <pthread.h>


int N = 100;
int turn = 0; // 쓰레드의 교대 순서를 결정하는 변수
int flag[2] = {0}; // 쓰레드들이 critical section에 들어가기 위해 대기하는 변수

void *thread_func(void *arg) {
    int thread_id = *(int *)arg;
    int other = 1 - thread_id; // 다른 쓰레드의 번호
    int start = thread_id * (N / 2) + 1; // 시작 숫자
    int end = (thread_id + 1) * (N / 2); // 끝 숫자

    for (int i = start; i <= end; ++i) {
        flag[thread_id] = 1; // 현재 쓰레드가 critical section에 들어가고 싶어 함
        turn = other; // 다른 쓰레드에게 차례를 양보
        while (flag[other] && turn == other); // 다른 쓰레드가 들어가 있고, 다른 쓰레드의 차례일 동안 대기

        // critical section
        printf("Thread %d: %d\n", thread_id, i * 3);

        flag[thread_id] = 0; // critical section을 나가면서 flag를 해제
    }

    return NULL;
}

int main() {
    pthread_t threads[2];
    int thread_ids[2] = {0, 1};

    pthread_create(&threads[0], NULL, thread_func, &thread_ids[0]);
    pthread_create(&threads[1], NULL, thread_func, &thread_ids[1]);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}

