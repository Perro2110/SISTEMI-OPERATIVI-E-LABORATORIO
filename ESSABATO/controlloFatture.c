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
    printf("numero di richieste effettuate/servite : %d \n", var);
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
    int fd;

    if (argv[1][0] != '/')
    {
        printf("Errore! Il nome specificato non e' un direttorio assoluto.\n");
        exit(2);
    }
    fd = open(argv[1], O_RDONLY);

    // n.b fd è un int
    if (fd < 0)
    {
        perror("open");
    }
    close(fd);

    int pid1;
    int pid2;
    int status;
    int p1p2[2];
    int p2p0[2];
    char nome[30];
    char stringa_da_ricevere[200];
    printf("Inserisci nome di persona da analizzare \n");
    scanf("%s", nome);

    while (strcmp("esci", nome) != 0)
    {
        if (pipe(p1p2) < 0)
        {
            perror("pipe");
            exit(2);
        }
        if (pipe(p2p0) < 0)
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
            signal(SIGINT, SIG_DFL);
            close(p2p0[0]);
            close(p2p0[1]);
            // ridirezione stdOut
            close(p1p2[0]);
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            execlp("grep", "grep", nome, argv[1], (char *)0);
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

            // ridirezione stdOut
            close(p2p0[0]);
            close(1);
            dup(p2p0[1]);
            close(p2p0[1]);

            execlp("grep", "grep", "-c", "da pagare", (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }
        // sono il parde P0
        close(p1p2[0]);
        close(p1p2[1]);
        wait(&status);
        wait(&status);
        close(p2p0[1]);
        int nread = read(p2p0[0], stringa_da_ricevere, 200);
        
        if (nread < 0)
        {
            printf("errore nella lettura della pipe \n");
            exit(0);
        }

        close(p2p0[0]);
        stringa_da_ricevere[nread] = '\0';
        printf("%s deve pagare %s \n", nome, stringa_da_ricevere);
        var++;

        printf("Inserisci nome di persona da analizzare \n");
        scanf("%s", nome);
    }
    printf("numero di richieste effettuate/servite : %d", var);
}
