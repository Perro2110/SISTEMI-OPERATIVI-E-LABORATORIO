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
    printf("letti %d byte", var);
    exit(0);
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, sig_handler);
    if (argc != 3)
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
    char path[500];
    sprintf(path, "%s/%s.txt", argv[1], argv[2]);
    fd = open(path, O_RDONLY);
    // n.b fd è un int
    if (fd < 0)
    {
        perror("open");
    }
    close(fd);

    int pid1, pid2;
    int status;
    int p0p1[2];
    int p2p0[2];
    char stringa_da_ricevere[100];
    while (1)
    {
        if (pipe(p0p1) < 0)
        {
            perror("pipe");
            exit(1);
        }
        if (pipe(p2p0) < 0)
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
            close(p0p1[1]);
            int nread = read(p0p1[0], stringa_da_ricevere, 100);
            close(p0p1[0]);
            stringa_da_ricevere[nread] = '\0';

            pid2 = fork();
            if (pid2 < 0)
            {
                perror("fork fallita :");
                exit(3);
            }
            if (pid2 == 0)
            { // FIGLIO P2
                signal(SIGINT, SIG_DFL);
                close(p0p1[0]);
                close(p0p1[1]);
                // ridirezione stdOut
                close(p2p0[0]);
                close(1);
                dup(p2p0[1]);
                close(p2p0[1]);

                execlp("grep", "grep", stringa_da_ricevere, path, (char *)0);
                perror("execlp non eseguita .. ?");
                exit(7);
            }
            // sono P1
            close(p2p0[0]);
            close(p2p0[1]);
            exit(1);
        }
        close(p0p1[0]);
        printf("inserisci nome persona \n");
        scanf("%s",stringa_da_ricevere);
        write(p0p1[1], stringa_da_ricevere, 100);
        close(p0p1[1]);

        wait(&status);
        wait(&status);

        close(p2p0[1]);
        int nread = read(p2p0[0], stringa_da_ricevere, 100);
        var += nread;
        close(p2p0[0]);
        stringa_da_ricevere[nread] = '\0';
        printf("%s \n", stringa_da_ricevere);
    }
}
