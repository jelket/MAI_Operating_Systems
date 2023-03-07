#include "unistd.h"
#include "stdio.h"

int main()
{
    char filename[100];
    char buf[100];
    int nums[3];
    int krya = 0;
    scanf("%s", filename);
    //read(filename,buf,100);
    FILE *file = fopen(filename,"w");

    int fd[2];
	pipe(fd);
    int id = fork();
	if (id == -1){
		perror("fork error");
		return -1;
	}if(id > 0){
        printf("[%d] It's parent. Child id: %d\n", getpid(), id);
        fflush(stdout);
        int x, y, z;
        scanf("%d %d %d", &x, &y,&z);
        read(krya,nums,3*sizeof(int));

        write(fd[1], nums[0], sizeof(int));
        write(fd[1], &y, sizeof(int));
        write(fd[1], &z, sizeof(int));

    }if (id == 0){
        int x, y, z;
        float res1, res2;
        printf("[%d] It's child\n", getpid());
        fflush(stdout);
        read(fd[0], &x, sizeof(int));
        read(fd[0], &y, sizeof(int));
        read(fd[0], &z, sizeof(int));

        if((y == 0)||(z == 0)){
            return -1;
        }

        res1 = x / y;
        res2 = res1 / z;

        fprintf(file,"%f", res2);

        fclose(file);

        close(fd[0]);
        close(fd[1]);

        return 0;
	}
}