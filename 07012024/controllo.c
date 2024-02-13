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
    printf("%d",var);
    exit(0);
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
    int pid1;
    int pid2;
    int status;
    char cognome[50];
    char Libro[50];
    char path[400];
    int p1p2[2];
    int p2p0[2];
    char stringa_da_ricevere[500];

    signal(SIGINT, sig_handler);
    
    printf("inserire nome libro \n");
    scanf("%s", Libro);
    printf("inserisci cognome persona \n");
    scanf("%s", cognome);
    
    sprintf(path,"%s/%s/%s.txt", argv[1],Libro,cognome);

    while (strcmp(Libro,"esci") != 0 && strcmp(cognome,"esci") != 0)
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

            close(p1p2[0]);
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);
            execlp("sort", "sort","-n",path, (char *)0);
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
        { // FIGLIO P1
            signal(SIGINT, SIG_DFL);

            close(p1p2[1]);
            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);

            close(p2p0[0]);
            close(1);
            dup(p2p0[1]);
            close(p2p0[1]);

            execlp("grep", "grep","ingresso", (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }
        // padre
        close(p1p2[0]);
        close(p1p2[1]);
        close(p2p0[1]);
        int nread = read(p2p0[0],stringa_da_ricevere,sizeof stringa_da_ricevere);
        var += nread;
        close(p2p0[0]);
        stringa_da_ricevere[nread] = '\0';
        printf("%s \n",stringa_da_ricevere);
        printf("inserire nome libro \n");
        scanf("%s", Libro);
        printf("inserisci cognome persona \n");
        scanf("%s", cognome);
        sprintf(path, "%s/%s/%s.txt", argv[1], Libro, cognome);
    }
    printf("%d", var);
}
