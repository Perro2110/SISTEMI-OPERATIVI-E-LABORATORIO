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
    printf("numero richieste %d", var);
    exit(0);
}

int main(int argc, char const *argv[])
{
    int fd;
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

    if( (fd = open(argv[1], __O_DIRECTORY)) < 0 ) {
        perror("Il nome specificato non è una directory.\n");
        exit(3);
    }
    close(fd);

    signal(SIGINT, sig_handler);
    int pid1;
    int pid2;
    int p1p2[2];
    char file[100];
    char argomento[100];
    char path[200];
    int status;

    printf("Inserisci data di interesse \n");
    scanf("%s", file);
    printf("Inserisci argomento di interesse \n");
    scanf("%s", argomento);

    sprintf(path, "%s/%s.txt", argv[1], file);
    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
    }
    close(fd);

    while (strcmp(file, "fine") != 0 && strcmp(argomento, "fine") != 0)
    {

        if (pipe(p1p2) < 0)
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
        {
            // Figlio p1

            signal(SIGINT, SIG_DFL);
            close(p1p2[0]);
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            execlp("grep", "grep", argomento, path, (char *)0);
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
        {
            // Figlio p2
            signal(SIGINT, SIG_DFL);
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
        var++;
        wait(&status);
        wait(&status);

        printf("Inserisci data di interesse \n");
        scanf("%s", file);
        printf("Inserisci argomento di interesse \n");
        scanf("%s", argomento);

        sprintf(path, "%s/%s.txt", argv[1], file);
    }
    printf("numero richieste %d", var);
}
