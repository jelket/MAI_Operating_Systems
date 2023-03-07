#include "realization.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    int cmd = 0;

    (scanf("%d", &cmd));
        if (cmd == 1) {
            float res, x, dx;
            printf("Enter x: ");
            scanf("%f", &x);
            printf("Enter dx: ");
            scanf("%f", &dx);
            res = der(x, dx);
            printf("%f\n", res);
        }
        if (cmd == 2){
            long a;
            printf("Enter a: ");
            (scanf("%ld", &a));
            char *string;
            printf("Translate integer(%ld) from 10 base to 2 base   \n", a);
            string = translation(a);
            printf("%s\n", string);
            free(string);
        }
}