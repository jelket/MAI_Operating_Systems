#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>


int main(int argc, char* argv[])
{
    char *filename2 = argv[1];
    char *maped = "MapedFile";
    int numbers[3];
    double doubles[3];
    double res1, res2;
    int fd;
    char *ptr;

    fd = open(maped,  O_RDONLY  , 00400); /* open s.m object*/
    if(fd == -1){
        printf("Error file descriptor %s\n", strerror(errno));
        exit(1);
    }
    ptr = mmap(NULL, 3*sizeof(int), PROT_READ, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED){
        printf("Map failed in read process: %s\n", strerror(errno));
        exit(1);
    }
    int k = 0;
    for(int i = 0; i < sizeof(numbers) ;i++) {
        if (ptr[i] != 0) {
            numbers[k] = ptr[i];
            k++;
        }
    }

    if((numbers[1] == 0)||(numbers[2] == 0)){
        return -1;
    }
    for(int i = 0; i < 3 ;i++) {
        doubles[i] = numbers[i];
    }

    res1 = doubles[0] / doubles[1];
    res2 = res1 / doubles[2];

    FILE *file = fopen(filename2,"w");
    fprintf(file,"%f", res2);
    fclose(file);
    close(fd);

    return 0;
}