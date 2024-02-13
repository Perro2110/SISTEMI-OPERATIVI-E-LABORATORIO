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
printf("Risposto a %d richieste",var);
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

    int fd;
    if (argv[1][0] != '/')
    {
        printf("Errore! Il nome specificato non e' un direttorio assoluto.\n");
        exit(2);
    }

    if ((fd = open(argv[1], __O_DIRECTORY)) < 0)
    {
        perror("Il nome specificato non è una directory.\n");
        exit(3);
    }
    close(fd);
    int pid1;
    int pid2;
    int status;
    int p1p2[2];
    int p2p0[2];
    char path[250];
    char nome_fornitore[50];
    char nome_applicazione[20];
    char stringa_da_ricevere[50];
    printf("inserisci nome fornitore di interesse \n");
    scanf("%s", nome_fornitore);
    printf("inserisci nome applicazione di interesse \n");
    scanf("%s", nome_applicazione);
    sprintf(path, "%s/%s.txt", argv[1], nome_fornitore);
    fd = open(path, O_RDONLY);
    // n.b fd è un int
    if (fd < 0)
    {
        perror("open");
    }
    close(fd);
    while (strcmp(nome_applicazione, "fine") != 0 && strcmp(nome_fornitore, "fine") != 0)
    {
        if (pipe(p1p2) < 0)
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
            close(p2p0[0]);
            close(p2p0[1]);
            // ridirezione stdOut
            close(p1p2[0]);
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            execlp("grep", "grep", nome_applicazione, path, (char *)0);
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

            execlp("grep", "grep", "-c", "operativa", (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }
        // sono il padre
        close(p1p2[0]);
        close(p1p2[1]);
        close(p2p0[1]);
        wait(&status);
        wait(&status);
        var++;
        int nread = read(p2p0[0], stringa_da_ricevere, 50);
        close(p2p0[0]);
        stringa_da_ricevere[nread] = '\0';
        printf("attualmente attive: %s \n", stringa_da_ricevere);

        printf("inserisci nome fornitore di interesse \n");
        scanf("%s", nome_fornitore);
        printf("inserisci nome applicazione di interesse \n");
        scanf("%s", nome_applicazione);
        sprintf(path, "%s/%s.txt", argv[1], nome_fornitore);
        fd = open(path, O_RDONLY);
        // n.b fd è un int
        if (fd < 0)
        {
            perror("open");
        }
        close(fd);
    }
    printf("servite %d richieste \n",var);
}
