#!/bin/bash
#cancella_versioni_preliminari dir_articoli
# Matricola: 184789


##############################
#### CONTROLLO ARGOMENTI: ####
##############################

clear

if test $# -eq 1;then
    echo ok
else
    echo Numero insufficente di argomenti
    exit 1
fi

case $1 in 
    /*)
        echo "Non voglio un percorso assoluto"  
        exit 2
    ;;
    *)
        if test -d $1 -a -x $1;then
            echo "ok"
        else
            echo "cartella non trovata o non valida"
            exit 3        
        fi
    ;;
esac
dir=$1
echo "0"> /tmp/.counter.tmp
> /tmp/.counterName.tmp

PATH=$PATH:$(pwd)
export PATH 

cancella_versioni_preliminari_aux.sh "$dir"

cat  /tmp/.counterName.tmp

rm -f /tmp/.counter.tmp
rm -f /tmp/.counterName.tmp
