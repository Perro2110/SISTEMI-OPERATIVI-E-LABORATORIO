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
    printf("\nservite %d richieste\n", var);
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

    if (argv[1][0] != '/')
    {
        printf("Errore! Il nome specificato non e' un file assoluto.\n");
        exit(2);
    }

    int fd;
    fd = open(argv[1], O_RDONLY);
    // n.b fd è un int
    if (fd < 0)
    {
        perror("open");
    }
    close(fd);

    char prefisso[20];
    char cognome[20];
    int pid1;
    int pid2;
    int status;
    int p1p2[2];
    printf("inserire cognome \n");
    scanf("%s", cognome);
    printf("inserire prefisso telefonico \n");
    scanf("%s", prefisso);

    while (strcmp("fine", cognome) != 0 && strcmp("fine", prefisso) != 0)
    {
        if (pipe(p1p2) < 0)
        {
            perror("pipe");
            exit(1);
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
            // UTILIZZO DI ISTRUZIONI UNIX ATTRAVERSO:
            execlp("grep", "grep", cognome, argv[1], (char *)0);
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
            // UTILIZZO DI ISTRUZIONI UNIX ATTRAVERSO:
            execlp("grep", "grep", prefisso, (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }
        // sono il PADRE
        close(p1p2[0]);
        close(p1p2[1]);

        wait(&status);
        wait(&status);

        var++;

        printf("inserire cognome \n"); // avrei potuto usare una struttura iterativa diversa come do while
        scanf("%s", cognome);          // per mia leggibilità ho prediletto il while
        printf("inserire prefisso telefonico \n");
        scanf("%s", prefisso);
    }
    printf("\nservite %d richieste\n", var);
}
