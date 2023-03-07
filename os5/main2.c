#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>


typedef enum {
    FIRST,
    SECOND,
} CONTEXT;

CONTEXT r = FIRST;

const char* libName1 = "libfirst.so";
const char* libName2 = "libsecond.so";

float (*der)(float, float) = NULL;
char* (*translation)(long x) = NULL;
char *err;

void *libHandle = NULL;

void loadDLibs(CONTEXT context){
    const char *name;
    if(context == FIRST){
        name = libName1;
    } else{
        name = libName2;
    }

    libHandle = dlopen(name, RTLD_LAZY);
    if(!libHandle){
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
}

void unloadDLibs(){
    dlclose(libHandle);
}

void loadContext(){
    loadDLibs(r);
    der = dlsym(libHandle, "der");
    translation = dlsym(libHandle, "translation");
    if((err = dlerror())) {
        fprintf(stderr, "%s\n", err);
        exit(EXIT_FAILURE);
    }
}

void changeContext(){
    unloadDLibs();
    if(r == FIRST){
        r = SECOND;
    } else {
        r = FIRST;
    }

    loadContext();
}

int main(){
    r = FIRST;
    loadContext();

    int cmd = 0;

    scanf("%d", &cmd);

        if(cmd == 1) {
            float res, x, dx;
            printf("Enter x: ");
            scanf("%f", &x);
            printf("Enter dx: ");
            scanf("%f", &dx);
            res = der(x, dx);
            printf("%f\n", res);
        }
        else{
            long x;
            if(scanf("%ld", &x)== EOF){
                return 0;
            }

            char *string;
            printf("Translate integer(%ld) from 10 base to ", x);
            if(r == FIRST) {
                printf("2");
            }else{
                printf("3");
            }
            puts(" base");
            string = translation(x);
            printf("%s\n", string);
            free(string);
        }
    unloadDLibs();
}