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

// test_eseguiti.c dir data
static volatile sig_atomic_t c = 0;

void sig_handler(int sig)
{
    printf("Letti da P2 byte: %d  \n", c);
    exit(0);
}

int main(int argc, char const *argv[])
{
    int pid, pid2;
    int status;
    char stringa_da_ricevere[100];
    char path[150];
    char buff[150];
    int vbyte = 0;

    sprintf(path, "%s/%s.txt", argv[1], argv[2]);
    int fd = open(path, O_RDONLY);
    // n.b fd è un int
    if (fd < 0)
    {
        perror("open");
    }
    close(fd);

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

    int p0p1[2];
    int p2p0[2];
    signal(SIGINT, sig_handler);
    while (1)
    {

        if (pipe(p0p1) < 0)
        {
            perror("pipe");
            exit(2);
        }

        if (pipe(p2p0) < 0)
        {
            perror("pipe");
            exit(2);
        }

        pid = fork();

        if (pid < 0)
        {
            perror("fork fallita :");
            exit(3);
        }

        if (pid == 0)
        { // figlio 1
            signal(SIGINT, SIG_DFL);
            close(p0p1[1]);
            read(p0p1[0], stringa_da_ricevere, sizeof stringa_da_ricevere);
            close(p0p1[0]);

            pid2 = fork();

            if (pid2 < 0)
            {
                perror("fork fallita :");
                exit(3);
            }

            if (pid2 == 0)
            {
                close(p2p0[0]);
                close(1);
                dup(p2p0[1]);
                close(p2p0[1]);

                execlp("grep", "grep", stringa_da_ricevere, path, (char *)0);
                perror("execlp non eseguita .. ?");
                exit(7);
            }
            //sono p1
            close(p2p0[0]);
            close(p2p0[1]);
            exit(0);
        }

            //sono il padre
            printf("Inserire nome richiesto: \n");

            scanf("%s", stringa_da_ricevere);

            close(p0p1[0]);
            write(p0p1[1], stringa_da_ricevere, sizeof stringa_da_ricevere);
            close(p0p1[1]);

            close(p2p0[1]);
            vbyte=0;
            vbyte += read(p2p0[0], buff, sizeof buff);
            c += vbyte;

            buff[vbyte] = '\0';
            close(p2p0[0]);
            printf("%s", buff);
        
    }
}
