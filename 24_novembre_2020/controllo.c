//********************************************
// Librerie necessarie:
//*********************************************

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <asm-generic/fcntl.h>

// controllo \dir 

static volatile sig_atomic_t val = 0;


void morte_heder(int sig) {
    printf("trovati n byte: %d ",val);
    exit(0);
}


int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("errore: numero argomenti\n");
        exit(1);
    }

    if(argv[1][0] != '/') {
        printf("Errore! Il nome specificato non e' un direttorio assoluto.\n");
        exit(2);
    }
/*
    int fd;
    if( (fd = open(argv[1], O_DIRECTORY)) < 0 ) { //n.b fd è un int
        perror("Il nome specificato non è una directory.\n");
        exit(3);
    }
    close(fd);
*/
    int p1p2[2];
    int p2p0[2];
    int p1,p2; //pid
    int status;
    char cognome [50];
    char nomeLibro [50];
    char path [150];
    char buff [500];

    printf("inserire Cognome \n");
    scanf("%s",cognome);
    printf("inserire nomeLibro \n");
    scanf("%s",nomeLibro);
    
    while(strcmp(cognome,"esci")!=0 && strcmp(nomeLibro,"esci")!=0){
        pipe(p1p2);
        pipe(p2p0);
        signal(SIGINT,morte_heder); 
        sprintf(path, "%s/%s/%s.txt",argv[1],nomeLibro,cognome); //forse doveva farlo il p1, testo poco chiaro
        
        /*
        int fd = open(path, O_RDONLY); //n.b fd è un int
        if (fd < 0) {
            perror("open");
            continue;
        }
        close(fd);
        */

        p1=fork();
        if(p1 < 0) {
            perror("fork fallita :");
            exit(3);
        }
        if(p1 == 0) { // FIGLIO

            signal(SIGINT,SIG_IGN); //dovrebbe essere inutile ma per sicurezza...

            close(p2p0[0]); //
            close(p2p0[1]); // non le tocca mai 
   
            close(p1p2[0]);
            close(1);         // ri-direziono lo stdout
            dup(p1p2[1]);     //
            close(p1p2[1]);

            execlp("sort", "sort",path,(char*) 0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }
        //sono il padre
        p2=fork();
        if(p2 < 0) {
            perror("fork 2 fallita :");
            exit(3);
        }
        if(p2 == 0) { // FIGLIO P2
            signal(SIGINT,SIG_IGN); //dovrebbe essere inutile ma per sicurezza...
            close(p1p2[1]);
            close(0);         // ri-direziono lo stdIN
            dup(p1p2[0]);     //
            close(p1p2[0]);

            close(p2p0[0]);
            close(1);         // ri-direziono lo stdout
            dup(p2p0[1]);     //
            close(p2p0[1]);

            execlp("grep", "grep","ingresso",(char*) 0);
            perror("execlp non eseguita .. ?");
            exit(7);
        }
        //sono il padre
        close(p1p2[0]);
        close(p1p2[1]);
        close(p2p0[1]);
        wait(&status);

        int byte_ricercati;
        byte_ricercati = read(p2p0[0],buff,sizeof(buff) );
        printf("%s",buff);
        val += byte_ricercati;
        
        close(p2p0[0]);
    
        printf("inserire Cognome \n");
        scanf("%s",cognome);
        printf("inserire nomeLibro \n");
        scanf("%s",nomeLibro);
    }
    printf("Numero byte letti %d",val);
    return 0;
}
