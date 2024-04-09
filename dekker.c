#include <stdio.h>
#include <pthread.h>


int N = 100;
int turn = 0; // 쓰레드의 교대 순서를 결정하는 변수
int flag[2] = {0, 0}; // 쓰레드들이 critical section에 들어가기 위해 대기하는 변수

void *thread_func(void *arg) {
    int thread_id = *(int *)arg;
    int start = thread_id * (N / 2) + 1;
    int end = (thread_id + 1) * (N / 2);
    
    for (int i = start; i <= end; ++i) {
        flag[thread_id] = 1;
        while (flag[1 - thread_id]) {
        	if (turn != thread_id) {
        		flag[thread_id] = 0;
        		while (turn != thread_id);
        		flag[thread_id] = 1;
        	}
        }
        
        // critical section
        printf("Thread %d: %d\n", thread_id, i * 3);
        
        turn = 1 - thread_id;
        flag[thread_id] = 0;
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
