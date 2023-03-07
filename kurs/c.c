#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int fromA = atoi(argv[1]);
    int toA = atoi(argv[2]);
    int toB = atoi(argv[3]);
    size_t size;

    while (read(fromA, &size, sizeof(size_t)) > 0){
        char *str = (char*) malloc(size);
        read(fromA, str, size);
        printf("C is alive\n");
        printf("string received from A: %s\n", str);
        write(toB, &size, sizeof(size_t));
        int check = 1;
        write(toA, &check, sizeof(int));
        free(str);
    }
    close(fromA);
    close(toA);
    close(toB);

    return 0;
}