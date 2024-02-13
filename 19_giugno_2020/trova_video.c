#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>

static volatile sig_atomic_t var = 0;

void sig_heder(int sig)
{
    printf("svolte: %d", var);
    exit(0);
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("errore: numero argomenti\n");
        exit(1);
    }

    if (argv[1][0] == '/')
    {
        printf("Errore! Il nome specificato e' un direttorio assoluto.\n");
        exit(2);
    }

/*  int fd;
    if ((fd = open(argv[1], O_DIRECTORY)) < 0)
    {
        perror("Il nome specificato non è una directory.\n");
        exit(3);
    }
    close(fd);
*/
    int pid1;
    int pid2;
    char tipo[100];
    char file[100];
    char path[200];
    int status;
    int p1p2[2];
printf("hi");
    while (1)
    {
        printf("hi");
        if (pipe(p1p2) < 0)
        {
            perror("pipe");
            exit(2);
        }
        
        var++;
        signal(SIGINT, sig_heder);
        printf("tipo di video:\n");
        scanf("%s", tipo);
        printf("data interesse [YYYYMM] \n");
        scanf("%s", file);
        sprintf(path, "%s/%s.txt", argv[1], file);

        pid1 = fork();
        if (pid1 < 0)
        {
            perror("fork fallita :");
            exit(3);
        }
        if (pid1 == 0)
        { // FIGLIO
            // P1
            signal(SIGINT, SIG_DFL);
            close(p1p2[0]);
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);
            execlp("grep", "grep ", tipo, path, (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }

        pid2 = fork();

        if (pid2 < 0)
        {
            perror("fork fallita :");
            exit(3);
        }
        if (pid2 == 0)
        { // FIGLIO
            // P2
            close(p1p2[1]);
            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);
            signal(SIGINT, SIG_DFL);
            execlp("sort", "sort", (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }
        close(p1p2[0]);
        close(p1p2[1]);
    }
}
