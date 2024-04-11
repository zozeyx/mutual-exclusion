#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

sem_t semaphore;
int critical_section = 1;

void *func0(void *arg) {
    sem_wait(&semaphore);
    while(critical_section != 1){}
    for(int i = 0; i < 25; i++){
        printf("thread 0 : %d\n", critical_section * 3); critical_section++;
    }
    sem_post(&semaphore);
    pthread_exit(NULL);
}
void *func1(void *arg) {
    sem_wait(&semaphore);
    while(critical_section != 26){}
    for(int i = 0; i < 25; i++){
        printf("thread 1 : %d\n", critical_section * 3); critical_section++;
    }
    sem_post(&semaphore);
    pthread_exit(NULL);
}
void *func2(void *arg) {
    sem_wait(&semaphore);
    while(critical_section != 51){}
    for(int i = 0; i < 25; i++){
        printf("thread 2 : %d\n", critical_section * 3); critical_section++;
    }
    sem_post(&semaphore);
    pthread_exit(NULL);
}
void *func3(void *arg) {
    sem_wait(&semaphore);
    while(critical_section != 76){}
    for(int i = 0; i < 25; i++){
        printf("thread 3 : %d\n", critical_section * 3); critical_section++;
    }
    sem_post(&semaphore);
    pthread_exit(NULL);
}
int main(){
    pthread_t tid0, tid1, tid2, tid3;
    sem_init(&semaphore, 0, 1); // 세마포 초기값은 1로 설정
    
    pthread_create(&tid0, NULL, func0, NULL);
    pthread_create(&tid1, NULL, func1, NULL);
    pthread_create(&tid2, NULL, func2, NULL);
    pthread_create(&tid3, NULL, func3, NULL);
    
    pthread_join(tid0, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    
    sem_destroy(&semaphore);

    return 0;
}
