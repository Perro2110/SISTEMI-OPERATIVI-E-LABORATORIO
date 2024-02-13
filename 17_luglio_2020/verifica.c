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
    printf("richieste: %d ",var);
    exit(0);
}

// verifica fileBollette
int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("errore: numero argomenti\n");
        exit(1);
    }

    if (argv[1][0] != '/')
    {
        printf("Errore! Il nome specificato non e' un assoluto.\n");
        exit(2);
    }

    int pid1 = 0, pid2 = 0, pid3 = 0;
    int p1p2[2];
    int p2p3[2];
    int p3p0[2];
    char path[150];
    char tipo[100];
    char stringa_da_ricevere[100];

    signal(SIGINT,sig_handler);

    sprintf(path, "%s.txt", argv[1]);
    int fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
    }
    close(fd);

    printf("Inserire tipo: \n");
    scanf("%s", tipo);

    while (strcmp(tipo,"esci")!=0)
    {

        if (pipe(p1p2) < 0)
        {
            perror("pipe");
            exit(1);
        }

        if (pipe(p2p3) < 0)
        {
            perror("pipe");
            exit(1);
        }

        if (pipe(p3p0) < 0)
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
            signal(SIGINT,SIG_DFL);
            close(p2p3[0]);
            close(p2p3[1]);
            close(p3p0[0]);
            close(p3p0[1]);

            close(p1p2[0]);
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            execlp("grep", "grep", tipo, argv[1], (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }
        // Padre

        pid2 = fork();
        if (pid2 < 0)
        {
            perror("fork fallita :");
            exit(3);
        }
        if (pid2 == 0)
        { // FIGLIO P2
            signal(SIGINT,SIG_DFL);
            close(p3p0[0]);
            close(p3p0[1]);

            close(p1p2[1]);
            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);

            close(p2p3[0]);
            close(1);
            dup(p2p3[1]);
            close(p2p3[1]);

            execlp("grep", "grep", "da pagare", (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }

        // Padre

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

            close(p2p3[1]);
            close(0);
            dup(p2p3[0]);
            close(p2p3[0]);

            close(p3p0[0]);
            close(1);
            dup(p3p0[1]);
            close(p3p0[1]);

            execlp("sort", "sort", "-n","-r", (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }

        // padre
        close(p1p2[0]);
        close(p1p2[1]);
        close(p2p3[0]);
        close(p2p3[1]);

        close(p3p0[1]);
        int nread = read(p3p0[0],stringa_da_ricevere,sizeof stringa_da_ricevere);
        close(p3p0[0]);
        stringa_da_ricevere[nread] = '\0';
        printf("%s",stringa_da_ricevere);

        var++;
        printf("\n Inserire tipo: \n");
        scanf("%s", tipo);

    }
    printf("richieste: %d",var);
    return 0;
}
