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
printf("val: %d \n",var);
exit(0);
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("errore: numero argomenti\n");
        exit(1);
    }
    signal(SIGINT,sig_handler);
    char path[500];
    char nome[200];
    char nums[20];
    char stringa_da_ricevere[100];
    int num;
    int fd;
    sprintf(path, "%s.txt", argv[1]);
    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
    }
    close(fd);

    int pid1;
    int pid2;
    int pid3;
    int status;

    int p1p2[2];
    int p2p3[2];
    int p3p0[2];

    printf("inserire nome spettacolo: \n");
    scanf("%s", nome);
    printf("inserire N: \n");
    scanf("%d", &num);

    while (num != 0)
    {
        sprintf(nums, "%d", num);
        if (pipe(p1p2) < 0)
        {
            perror("pipe");
            exit(2);
        }

        if (pipe(p2p3) < 0)
        {
            perror("pipe");
            exit(2);
        }

        if (pipe(p3p0) < 0)
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
            close(p2p3[0]);
            close(p2p3[1]);
            close(p3p0[0]);
            close(p3p0[1]);

            // ridirezione stdOut
            close(p1p2[0]);
            close(1);
            dup(p1p2[1]);
            close(p1p2[1]);

            // UTILIZZO DI ISTRUZIONI UNIX ATTRAVERSO:
            execlp("grep", "grep", nome, path, (char *)0);
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
            close(p3p0[0]);
            close(p3p0[1]);

            // ridirezione stdIn
            close(p1p2[1]);
            close(0);
            dup(p1p2[0]);
            close(p1p2[0]);

            // ridirezione stdOut
            close(p2p3[0]);
            close(1);
            dup(p2p3[1]);
            close(p2p3[1]);

            // UTILIZZO DI ISTRUZIONI UNIX ATTRAVERSO:
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
            close(p1p2[0]);
            close(p1p2[1]);

            // ridirezione stdIn
            close(p2p3[1]);
            close(0);
            dup(p2p3[0]);
            close(p2p3[0]);

            // ridirezione stdOut
            close(p3p0[0]);
            close(1);
            dup(p3p0[1]);
            close(p3p0[1]);

            // UTILIZZO DI ISTRUZIONI UNIX ATTRAVERSO:
            execlp("head", "head", "-n", nums, (char *)0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }
        // Sono il parde
        close(p1p2[0]);
        close(p1p2[1]);
        close(p2p3[0]);
        close(p2p3[1]);
        close(p3p0[1]);
        wait(&status);
        wait(&status);
        wait(&status);
        // per leggere da pipe n.b non devi aver chiuso o ridiretto pipe
        int nread = read(p3p0[0], stringa_da_ricevere, 100);
        close(p3p0[0]);
        stringa_da_ricevere[nread] = '\0';
        printf(" %s \n", stringa_da_ricevere);
        var++;
        printf("inserire nome spettacolo: \n");
        scanf("%s", nome);
        printf("inserire N: \n");
        scanf("%d", &num);
    }
    printf("val: %d \n",var);
}
