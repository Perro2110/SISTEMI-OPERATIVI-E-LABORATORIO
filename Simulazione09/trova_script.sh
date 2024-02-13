#!/bin/bash
#184789
#trova_script dir

if test $# -ne 1;then
    echo "errore numero di argomenti non corretto"
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
        *) echo "uso: trova_script dir"
                echo "La dir deve essere chiamata con nomi assoluti"
                exit 2;;
esac

dir=$1
shift

if ! test -e $HOME/script.txt;then
    >$HOME/script.txt
    echo "creato file script.txt"
else
    echo file gia esistente
fi

echo "0"> /tmp/.counter.tmp
> /tmp/.counterName.tmp



SCRIPT=$HOME/script.txt
export SCRIPT

PATH=$PATH:$(pwd)
export PATH 

trova_script_Bl.sh $dir

echo $(cat /tmp/.counterName.tmp)

