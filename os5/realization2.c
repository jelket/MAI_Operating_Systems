#include "realization.h"

#include <stdlib.h>
#include <string.h>

const float pi = 3.1415926535897;

float cosine(float x)
{
    int div = (int)(x / pi);
    x = x - (div * pi);
    char sign = 1;
    if (div % 2 != 0)
        sign = -1;

    float result = 1.0;
    float inter = 1.0;
    float num = x * x;
    for (int i = 1; i <= 16; i++)
    {
        float comp = 2.0 * i;
        float den = comp * (comp - 1.0);
        inter *= num / den;
        if (i % 2 == 0)
            result += inter;
        else
            result -= inter;
    }

    return sign * result;
}

float der(float x, float dx)
{
    float res;
    res = (cosine((x + dx)) - cosine((x - dx))) / (2 * dx);
    return res;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "DanglingPointers"
char* translation(long x){
    char *res = calloc(1, sizeof(char));
    res[0] = '\0';
    if(x == 0){
        char *tmp = calloc(strlen(res) + 2, sizeof(char));
        strcpy(tmp+1, res);
        free(res);
        res = tmp;
        res[0] = '0';
    }
    while(x > 0){
        char ch = (x % 3) + '0';
        x /= 3;
        char *tmp = calloc(strlen(res) + 2, sizeof(char));
        strcpy(tmp+1, res);
        free(res);
        res = tmp;
        res[0] = ch;
    }
    return res;
}
#pragma clang diagnostic pop