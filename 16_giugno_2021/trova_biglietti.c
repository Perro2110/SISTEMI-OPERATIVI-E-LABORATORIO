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
    printf("\n %d",var);
    exit(0);
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("errore: numero argomenti\n");
        exit(1);
    }

    if (argv[1][0] == '/')
    {
        printf("Errore! Il nome specificato e' un assoluto.\n");
        exit(2);
    }

    signal(SIGINT,sig_handler);

    char Path[150];
    char data[100];
    char buff[100];
    int N = atoi(argv[2]);
    int pid;
    int status;

    int p1p2[2];
    int p2p3[2];
    int p3p0[2];
    int giorno;
    int mese;
    int anno;

    printf("inserire giorno mese e anno (-1 se si vuole  uscire dal programma) \n");
    scanf("%d", &giorno);
    scanf("%d", &mese);
    scanf("%d", &anno);

    while (giorno != -1 && mese != -1 && anno != -1)
    {
        sprintf(Path, "%s.txt", argv[1]);
        sprintf(data, "%d%d%d", giorno, mese, anno);
        pipe(p1p2);
        pipe(p2p3);
        pipe(p3p0);

        pid = fork();
        if (pid < 0)
        {
            perror("fork fallita :");
            exit(3);
        }
        if (pid == 0)
        { // FIGLIO P1
            signal(SIGINT, SIG_IGN);
            close(p2p3[0]);
            close(p2p3[1]);
            close(p3p0[0]);
            close(p3p0[1]);

            close(p1p2[0]);
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            execlp("grep", "grep", data, Path, (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }

        pid = fork();
        if (pid < 0)
        {
            perror("fork fallita :");
            exit(3);
        }
        if (pid == 0)
        { // FIGLIO P2
            signal(SIGINT, SIG_IGN);
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

            execlp("sort", "sort","-n", (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }
        pid = fork();
        if (pid < 0)
        {
            perror("fork fallita :");
            exit(3);
        }
        if (pid == 0)
        { // FIGLIO P3
            signal(SIGINT, SIG_IGN);
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

            execlp("head", "head", "-n", argv[2], (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }

        // Padre
        close(p1p2[0]);
        close(p1p2[1]);
        close(p2p3[0]);
        close(p2p3[1]);
        int nu_read = read(p3p0[0], buff, sizeof buff);

        close(p3p0[0]);

        write(1, buff, nu_read);
        var++;

        printf("inserire giorno mese e anno (-1 se si vuole  uscire dal programma) \n");
        scanf("%d", &giorno);
        scanf("%d", &mese);
        scanf("%d", &anno);
    }
    printf("\n %d", var);

    return 0;
}
