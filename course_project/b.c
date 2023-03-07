#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    int fromC = atoi(argv[1]);
    int fromA = atoi(argv[2]);

    size_t size;

    while (read(fromA, &size, sizeof(size_t)) > 0) {
        printf("B is alive\n");
        printf("Number of symbols A sent: %zu\n", size);
        read(fromC, &size, sizeof(size_t));
        printf("Number of symbols C received: %zu\n", size);
    }
    close(fromC);
    close(fromA);

    printf("C\n");

    return 0;
}