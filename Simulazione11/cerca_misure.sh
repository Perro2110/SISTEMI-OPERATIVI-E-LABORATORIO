#!/bin/bash
#184789
#cerca_misure dir header

if test $# -ne 2;then
    echo "numero di argomenti non valido"
    exit 1
fi

case $1 in
        /*)
            if test -d $1 -a -x $1;then
                echo "ok"
            else
                echo "cartella Assoluta non trovata o non valida"
                exit 1        
            fi
        ;;
        *) echo "uso: cerca_misure dir header"
                echo "La dir deve essere chiamata con nomi assoluti"
                exit 2;;
esac

dir=$1
shift 
header=$1
shift

if ! test -e $HOME/misure.txt;then
    echo "creata"
    echo "">$HOME/misure.txt
fi

echo "0"> /tmp/.counter.tmp
> /tmp/.counterName.tmp

MISURE=$HOME/misure.txt
export MISURE

PATH=$PATH:$(pwd)
export PATH 

cerca_misure_bl.sh $dir $header

echo "il nome della sottodirectory che contiene il maggior numero di file che soddisfano le condizioni di ricerca e' "
cat /tmp/.counterName.tmp 



