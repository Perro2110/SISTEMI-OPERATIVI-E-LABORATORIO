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
    printf("risposto a: %d richieste", var);
    exit(0);
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("errore: numero argomenti\n");
        exit(1);
    }

    signal(SIGINT,sig_handler);
    int pid1;
    int pid2;
    int pid3;
    int status;
    int p1p2[2];
    int p2p3[2];
    char giorno[10], mese[10], anno[10];
    char data[100];
    char path[150];

    sprintf(path, "var/local/ticket/%s.txt", argv[1]);
    int fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        exit(-2);
    }
    close(fd);


    printf("Inserire giorno \n");
    scanf("%s",giorno);

    printf("Inserire mese \n");
    scanf("%s",mese);

    printf("Inserire anno \n");
    scanf("%s",anno);

    sprintf(data, "%s%s%s", giorno, mese, anno);

    

    while (strcmp(giorno,"-1")!=0 && strcmp(mese,"-1")!=0 && strcmp(anno,"-1")!=0)
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

        pid1 = fork();
        if (pid1 < 0)
        {
            perror("fork fallita :");
            exit(3);
        }
        if (pid1 == 0)
        { // FIGLIO P1
            signal(SIGINT, SIG_DFL);
            // chiudo il superfluo
            close(p2p3[0]);
            close(p2p3[1]);

            // ridireziono
            close(p1p2[0]);
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            execlp("grep", "grep", data, path, (char *)0);
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
            // ridireziono in
            close(p1p2[1]);
            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);

            // ridireziono out
            close(p2p3[0]);
            close(1);
            dup(p2p3[1]);
            close(p2p3[1]);

            execlp("sort", "sort", "-n", (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }

        pid3 = fork();
        if (pid3 < 0)
        {
            perror("fork fallita :");
            exit(3);
        }
        if (pid3 == 0)
        { // FIGLIO P3
            signal(SIGINT, SIG_DFL);
            // chiudo il superfluo
            close(p1p2[0]);
            close(p1p2[1]);

            // ridireziono in
            close(p2p3[1]);
            close(0);
            dup(p2p3[0]);
            close(p2p3[0]);

            execlp("head", "head", "-n",argv[2], (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }
        // SONO CERTAMENTE IL PADRE
        //  chiudo il superfluo
        close(p1p2[0]);
        close(p1p2[1]);
        close(p2p3[0]);
        close(p2p3[1]);

        wait(&status);
        wait(&status);
        wait(&status);

        var++;
        printf("Inserire giorno \n");
        scanf("%s",giorno);

        printf("Inserire mese \n");
        scanf("%s",mese);

        printf("Inserire anno \n");
        scanf("%s",anno);
        sprintf(data, "%s%s%s", giorno, mese, anno);
    }
    printf("risposto a: %d richieste",var);
}