#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    int numbers[3];
    char *ptr;
    char filename[100];
    char *maped = "MapedFile";

    scanf("%s", filename);
    for(int i = 0; i < 3 ;i++) {
        scanf("%d", &numbers[i]);
    }

    unsigned int fd = open(maped, O_RDWR | O_CREAT  , S_IWRITE | S_IREAD); /* create s.m object*/
    if(fd == -1){
        printf("Error file descriptor \n");
        exit(1);
    }
    ptr = mmap(NULL, 3*sizeof(int), PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED)
    {
        printf("Map failed in write process: %s\n", strerror(errno));
        exit(1);
    }
    memcpy( ptr,numbers, 3*sizeof(int ));

    execl("child"," ",filename, NULL);

    close(fd);

    return 0;
}