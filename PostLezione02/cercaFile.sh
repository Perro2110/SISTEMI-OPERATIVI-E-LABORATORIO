#!/bin/bash
#cercaFile stringa dir num
# Matricola: 184789


##############################
#### CONTROLLO ARGOMENTI: ####
##############################

clear


if test $# -ne 3;then
    echo "mancanza di argomenti"
    exit 999 #inserito dopo... lol
fi

stringa=$1
shift


case $1 in
        /*)
            if test -d $1 -a -x $1;then
                echo "ok"
            else
                echo "cartella Assoluta non trovata o non valida"
                exit 1        
            fi
        ;;
        *) echo "uso: cercaFile stringa dir num"
                echo "La dir deve essere chiamata con nomi assoluti"
                exit 2;;
esac

dir=$1
shift

case $1 in
        *[!0-9]*) echo "uso: muoviFile num dirSorgente dirDestinazione ext1 ext2...extN"
                echo "num deve essere un numero"
                exit 3;;
esac

num=$1
shift

############# Mandero quindi: ##################
echo $stringa $dir $num 
################################################

PATH=$PATH:$(pwd)
export PATH 


# creo un file temporaneo per salvare i risultati parziali
echo "0" > /tmp/.counter.tmp
> /tmp/.counterName.tmp

cercaStringa.sh "$stringa" "$dir" "$num"
echo $(cat /tmp/.counterName.tmp)  #prendo cio che mi serve dal file .tmp

rm -f /tmp/.counter.tmp
rm -f /tmp/.counterName.tmp