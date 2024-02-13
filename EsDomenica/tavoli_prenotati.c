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


static volatile sig_atomic_t var = 0;

void sig_handler(int sig) {
    printf("Ricevute in totale %d richieste \n",var);
    exit(0);
}


int main(int argc, char const *argv[])
{
    signal(SIGINT,sig_handler);
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
    int fd;
    if ((fd = open(argv[1], __O_DIRECTORY)) < 0)
    {
        perror("Il nome specificato non è una directory.\n");
        exit(3);
    }
    close(fd);
    char ristorante[50];
    char dataInteresse[50];
    char N[50];
    char path[500];
    int pid1;
    int pid2;
    int pid3;
    int p1p2[2];
    int p2p3[2];
    int status;

    while (1)
    {

        printf("identificativo ristorante: \n");
        scanf("%s", ristorante);

        printf("inserire data di interesse: \n");
        scanf("%s", dataInteresse);

        printf("Numero N: \n");
        scanf("%s", N);

        sprintf(path, "%s/%s.txt", argv[1], dataInteresse);
        fd = open(path, O_RDONLY);
        // n.b fd è un int
        if (fd < 0)
        {
            perror("open");
            continue;
        }
        close(fd);

        if (pipe(p1p2) < 0)
        {
            perror("pipe");
            exit(2);
        }
        if (pipe(p2p3) < 0)
        {
            perror("pipe");
            exit(2);
        }

        pid1 = fork();
        if (pid1 < 0)
        {
            perror("fork fallita :");
            exit(3);
        }
        if (pid1 == 0)
        { // FIGLIO P1
            signal(SIGINT,SIG_DFL);
            close(p2p3[0]);
            close(p2p3[1]);

            // ridirezione stdOut
            close(p1p2[0]);
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            execlp("grep", "grep", ristorante, path, (char *)0);
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
        { // FIGLIO P2
            signal(SIGINT,SIG_DFL);
            // ridirezione stdIn
            close(p1p2[1]);
            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);

            // ridirezione stdOut
            close(p2p3[0]);
            close(1);
            dup(p2p3[1]);
            close(p2p3[1]);

            execlp("sort", "sort","-n","-r", (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }

        pid3 = fork();
        if (pid3 < 0)
        {
            perror("fork fallita :");
            exit(3);
        }
        if (pid3 == 0)
        { // FIGLIO P3
            signal(SIGINT,SIG_DFL);
            close(p1p2[0]);
            close(p1p2[1]);

            // ridirezione stdIn
            close(p2p3[1]);
            close(0);
            dup(p2p3[0]);
            close(p2p3[0]);

            execlp("head", "head","-n",N, (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }
        close(p1p2[0]);
        close(p1p2[1]);
        close(p2p3[0]);
        close(p2p3[0]);
        wait(&status);
        wait(&status);
        wait(&status);
        var++;
    }
}
