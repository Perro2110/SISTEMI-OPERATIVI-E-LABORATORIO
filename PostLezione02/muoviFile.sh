#!/bin/bash
# Matricola: 184789
#muoviFile num dirSorgente dirDestinazione ext1 ext2...extN

##############################
#### CONTROLLO ARGOMENTI: ####
##############################

clear


echo " "
echo "**************************************************"
echo "******************* NEL CHIAMANTE ****************"
echo "**************************************************"
echo " "

if test $# -ge 4;then 
    echo "Numero argomenti corretto"
else 
    echo "non argomenti sufficenti"
    exit 1
fi

case $1 in
        *[!0-9]*) echo "uso: muoviFile num dirSorgente dirDestinazione ext1 ext2...extN"
                echo "num deve essere un numero"
                exit 2;;
esac

num=$1;
shift

case $1 in
        /*)
            if test -d $1 -a -x $1;then
                echo "ok"
            else
                echo "cartella Assoluta non trovata o non valida"
                exit 3        
            fi
        ;;
        *) echo "uso: muoviFile num dirSorgente dirDestinazione ext1 ext2...extN"
                echo "La dirSorgente deve essere chiamata con nomi assoluti"
                exit 2;;
esac

dirSorgente=$1;
shift

case $1 in
        /*)
            if test -d $1 -a -x $1;then
                echo "ok"
            else
                echo "cartella Assoluta non trovata o non valida"
                exit 5        
            fi
        ;;
        *) echo "uso: muoviFile num dirSorgente dirDestinazione ext1 ext2...extN"
                echo "La dirDestinazione deve essere chiamata con nomi assoluti"
                exit 4;;
esac

dirDestinazione=$1;
shift

for i in $*;do 
    case $i in
            .*)
                echo "Estensione $i approvata" 
            ;;
            *) echo "uso: muoviFile num dirSorgente dirDestinazione ext1 ext2...extN"
                    echo "$i NON è UN ESTENSIONE "
                    exit 6;;
    esac
done

############# Mandero quindi: ##################
echo $num $dirSorgente $dirDestinazione $* 
################################################

PATH=$PATH:$(pwd)
export PATH 

#########################################################################################################################
################ creazione del file di appoggio temporaneo counter.tmp, dove salvare una riga ###########################
################                  per ciascun file copiato                                               ################
#########################################################################################################################                  
> /tmp/.counter.tmp

#########################################################################################################################  
################                  chiamata a ricerca.sh <parametri>                                      ################
#########################################################################################################################
ricerca.sh $num "$dirSorgente" "$dirDestinazione" $*  

echo " "
echo "**************************************************"
echo "******************* NEL CHIAMANTE ****************"
echo "**************************************************"
echo " "
echo $(wc -l < /tmp/.counter.tmp)  #prendo cio che mi serve dal file .tmp
echo " "
rm -f /tmp/.counter.tmp
