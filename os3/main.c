#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

char* sieve;
long long num;
char c;
char lego[100];
int m = 0;

void* sieve_step(void* i_void) {
    long long i = *(long long*)i_void;
    for (long long j = i * i; j <= num; j += i) {
        sieve[j] = 1;
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("./lab3 + число потоков\n");
        exit(1);
    }

    int threads_num = atoi(argv[1]);

    pthread_t* threads = (pthread_t*)calloc(threads_num, sizeof(pthread_t));

    long long* args = (long long*)malloc(threads_num * sizeof(long long));

    printf("Введите число для проверки: ");

    /*
     обьявлены выше
     char c;
    char lego[100];
    int m = 0;
     */

    while (true) {
        c = getchar();
        if (c == '\n') {
            lego[m] = 0;
            num = strtol(lego, (char **) NULL, 10);
            break;
        } else if (c == ' '){
            lego[m] = 0;
            num = strtol(lego, (char **) NULL, 10);
            break;
        } else if (c >= '0' && c <= '9') {
            lego[m] = c;
            m++;
        } else{
            printf("Неверный ввод\n");
            return 0;
        }

    }


  /*  scanf("%lld", &num);
    if(num == 0){
        printf("Неверный ввод\n");
        return 0;
    }*/

    sieve = (char*)calloc((num + 1), sizeof(char));

    sieve[0] = 1;
    sieve[1] = 1;

    int cur_thread = 0;
    for (long long i = 2; i * i <= num; ++i) {
        if (sieve[i] == 1) {
            continue;
        }
        if (cur_thread >= threads_num) {
            pthread_join(threads[cur_thread % threads_num], NULL);
        }

        args[cur_thread % threads_num] = i;
        pthread_create(&threads[cur_thread % threads_num], NULL, sieve_step, &args[cur_thread % threads_num]);
        ++cur_thread;
    }

    for (int i = 0; i < threads_num; ++i) {
        pthread_join(threads[i], NULL);
    }

    if (sieve[num] == 1) {
        printf("%lld не простое число\n", num);
    }
    else {
        printf("%lld простое число\n", num);
    }

    free(sieve);
    free(threads);
    free(args);
}