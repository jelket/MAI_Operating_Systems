#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t str_read(char **str_, int fd) {
    free(*str_);
    size_t str_size = 0;
    size_t cap = 4;
    char *str = (char*) malloc(sizeof(char) * cap);
    char c;

    while (read(fd, &c, sizeof(char)) == 1) {
        if (c == '\n') {
            break;
        }
        str[(str_size)++] = c;
        if (str_size == cap) {
            str = (char*) realloc(str, sizeof(char) * cap * 3 / 2);
            cap = cap * 3 / 2;
        }
    }
    str[str_size] = '\0';

    *str_ = str;
    return str_size;
}

size_t str_length(char *str) {
    size_t length = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        length++;
    }
    return length;
}

int main() {
    int fd_A_to_B[2];
    int fd_A_to_C[2];
    int fd_C_to_A[2];
    int fd_C_to_B[2];

    pipe(fd_A_to_B);
    pipe(fd_A_to_C);
    pipe(fd_C_to_A);
    pipe(fd_C_to_B);

    int id = fork();

    if (id < 0) {
        perror("Fork error");
        exit(1);
    }
    else if (id == 0) {
        close(fd_A_to_C[1]);
        close(fd_C_to_A[0]);
        close(fd_C_to_B[0]);
        close(fd_A_to_B[0]);
        close(fd_A_to_B[1]);

        char pac[3];
        sprintf(pac, "%d", fd_A_to_C[0]);

        char pca[3];
        sprintf(pca, "%d", fd_C_to_A[1]);

        char pcb[3];
        sprintf(pcb, "%d", fd_C_to_B[1]);

        execl("C", " ",  pac, pca, pcb, NULL);
    }
    else {
        int id2 = fork();
        if (id2 < 0) {
            perror("Fork error");
            exit(1);
        }
        else if (id2 == 0) {
            close(fd_A_to_C[0]);
            close(fd_A_to_C[1]);
            close(fd_C_to_A[0]);
            close(fd_C_to_A[1]);
            close(fd_C_to_B[1]);
            close(fd_A_to_B[1]);

            char pcb[2];
            sprintf(pcb, "%d", fd_C_to_A[0]);

            char pab[2];
            sprintf(pab, "%d", fd_C_to_B[0]);

            execl("B", " ",  pcb, pab, NULL);
        }
        else {
            close(fd_A_to_C[0]);
            close(fd_C_to_A[1]);
            close(fd_A_to_B[0]);
            close(fd_C_to_B[1]);
            close(fd_C_to_B[0]);

            char *str = NULL;
            while ((str_read(&str, 0)) > 0) {
                size_t size = str_length(str);
                write(fd_A_to_C[1], &size, sizeof(size_t));
                write(fd_A_to_C[1], str, size);
                write(fd_A_to_B[1], &size, sizeof(size_t));
                int ok;
                read(fd_C_to_A[0], &ok, sizeof(ok));
            }

            close(fd_C_to_A[0]);
            close(fd_A_to_C[1]);
            close(fd_A_to_B[1]);
        }
    }

    return 0;
}