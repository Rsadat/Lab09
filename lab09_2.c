#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int counter = 0;

pthread_mutex_t mlock;


pthread_cond_t is_one;
pthread_cond_t is_two;
pthread_cond_t is_three;

void * routine_even(void * arg)
{
    pthread_mutex_lock(&mlock);
    // event: counter is zero (happens first)
    if (counter == 0) {
        printf("zero\n");
        counter += 1;
	pthread_cond_signal(&is_one);
    }
    // event: counter is two
    while(counter != 2) {
        pthread_cond_wait(&is_two, &mlock);
    }
    printf("two\n");
    counter += 1;
C:\Users\rsadat\cs361 rsadat2@cs361.cs.uic.edu -p 12361    pthread_cond_signal(&is_three);


    pthread_mutex_unlock(&mlock);
    return NULL;
}


void * routine_odd(void * arg)
{
    pthread_mutex_lock(&mlock);
    // event: counter is one
    while(counter != 1) {

	pthread_cond_wait(&is_one, &mlock);
    }
    printf("one\n");
    counter += 1;
    pthread_cond_signal(&is_two);

    // event: counter is three
    while(counter != 3) {
	pthread_cond_wait(&is_three, &mlock);
    }
    printf("three\n");
    pthread_mutex_unlock(&mlock);

    return NULL;
}


int main(void)
{
    pthread_t even, odd;

    pthread_mutex_init(&mlock, NULL);

    pthread_cond_init(&is_one, NULL);

    pthread_cond_init(&is_two, NULL);

    pthread_cond_init(&is_three, NULL);

    pthread_create(&even, NULL, routine_even, NULL);
    pthread_create(&odd, NULL, routine_odd, NULL);

    pthread_join(even, NULL);
    pthread_join(odd, NULL);

    printf("Finished\n");

    return 0;
}
