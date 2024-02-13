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

void sig_handler(int sig)
{
    printf("ricevute/effetuate %d richieste", var);
    exit(0);
}

int main(int argc, char const *argv[])
{

    signal(SIGINT, sig_handler);
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

    char tipo[30];
    char data[30];
    char path[200];

    int pid1;
    int pid2;
    int status;
    int p1p2[2];

    printf("inserisci tipo di video: \n");
    scanf("%s", tipo);
    printf("inserisci data: \n");
    scanf("%s", data);

    while (1)
    {
        sprintf(path, "%s/%s.txt", argv[1], data);
        fd = open(path, O_RDONLY);
        if (fd < 0)
        {
            perror("open");
            exit(4);
        }
        close(fd);

        if (pipe(p1p2) < 0)
        {
            perror("pipe");
            exit(5);
        }

        pid1 = fork();
        if (pid1 < 0)
        {
            perror("fork fallita :");
            exit(3);
        }
        if (pid1 == 0)
        { // FIGLIO P1
            signal(SIGINT, SIG_DFL);
            // ridirezione stdOut
            close(p1p2[0]);
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            execlp("grep", "grep", tipo, path, (char *)0);
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
            signal(SIGINT, SIG_DFL);
            // ridirezione stdIn
            close(p1p2[1]);
            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);

            execlp("sort", "sort", "-n", "-r", (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }
        close(p1p2[0]);
        close(p1p2[1]);
        wait(&status);
        wait(&status);
        var++;
        printf("inserisci tipo di video: \n");
        scanf("%s", tipo);
        printf("inserisci data: \n");
        scanf("%s", data);
    }
}
