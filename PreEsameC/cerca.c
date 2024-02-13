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
    printf("effettuate %d richieste", var);
    exit(0);
}

void sig_handler_FIGLIO(int sig)
{
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("errore: numero argomenti\n");
        exit(1);
    }

    if (argv[1][0] != '/')
    {
        printf("Errore! Il nome specificato non e' un direttorio assoluto.\n");
        exit(2);
    }
    int fd;
    if ((fd = open(argv[1], __O_DIRECTORY)) < 0)
    {
        perror("Il nome specificato non è una directory.\n");
        exit(3);
    }
    close(fd);

    char path[500];
    char cognome[20];
    char genere[100];
    int numero;
    char N[20];
    int pid1;
    int pid2;
    int status;
    int p1p2[2];

    signal(SIGINT, sig_handler);

    printf("Inserire cognome autore: \n");
    scanf("%s", cognome);
    printf("inserire genere libro: \n");
    scanf("%s", genere);

    do
    {
        printf("iserire numero di risultati da visualizzare: \n");
        scanf("%d", &numero);
    } while (numero < 0);

    sprintf(N, "%d", numero);

    while (strcmp(cognome, "fine") != 0 && strcmp(genere, "fine") != 0)
    {
        sprintf(path, "%s/%s.txt", argv[1], genere);
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
            exit(6);
        }
        if (pid1 == 0)
        { // FIGLIO P1
            signal(SIGUSR1, sig_handler_FIGLIO);
            signal(SIGINT, SIG_DFL);
            pause();

            // ridirezione stdOut
            close(p1p2[0]);
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            execlp("grep", "grep", cognome, path, (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }

        pid2 = fork();
        if (pid2 < 0)
        {
            perror("fork fallita :");
            exit(6);
        }
        if (pid2 == 0)
        { // FIGLIO P2
            signal(SIGINT, SIG_DFL);

            // ridirezione stdIn
            close(p1p2[1]);
            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);

            execlp("head", "head", "-n", N, (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }
        // SONO IL PADRE
        close(p1p2[0]);
        close(p1p2[1]);
        sleep(1);
        kill(pid1,SIGUSR1);

        wait(&status);
        wait(&status);

        var++;
        printf("Inserire cognome autore: \n");
        scanf("%s", cognome);
        printf("inserire genere libro: \n");
        scanf("%s", genere);

        do
        {
            printf("iserire numero di risultati da visualizzare: \n");
            scanf("%d", &numero);
        } while (numero < 0);

        sprintf(N, "%d", numero);
    }
    printf("effettuate %d richieste", var);
}
