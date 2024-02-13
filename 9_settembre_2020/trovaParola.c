#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <bits/fcntl-linux.h>
#include <asm-generic/fcntl.h>

int main(int argc, char const *argv[])
{
    int fd; //per controlli
    char path[150];

    if (argc != 2)
    {
        printf("errore: numero argomenti\n");
        exit(1);
    }

    if(argv[1][0] != '/') {
        printf("Errore! Il nome specificato non e' un direttorio assoluto.\n");
        exit(2);
    }

    //sprintf(path, "%s.txt",argv[1]);
/*
    fd = open(argv[1], O_RDONLY);
    //n.b fd è un int
    if (fd < 0) {
        perror("open");
        exit(-1);
    }
    close(fd);
*/
    if( (fd = open(argv[1], O_DIRECTORY)) < 0 ) {
        perror("Il nome specificato non è una directory.\n");
        exit(3);
    }
    close(fd);
}
