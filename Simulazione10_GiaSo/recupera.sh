#!/bin/bash
#184789
#recupera dir recuperati titolo


if test $# -ne 3;then
    echo "numero argomenti non coincidente"
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
        *) echo "uso: recupera dir recuperati titolo"
                echo "La dir deve essere chiamata con nomi assoluti"
                exit 2;;
esac

dir=$1
shift

case $1 in
        /*)
            if test -d $1 -a -x $1;then
                echo "ok"
            else
                mkdir $1      
            fi
        ;;
        *) echo "uso: recupera dir recuperati titolo"
                echo "La dir deve essere chiamata con nomi assoluti"
                exit 2;;
esac

recuperati=$1
shift
titolo=$1

echo "0"> /tmp/.count.tmp
echo "0"> /tmp/.counter.tmp
> /tmp/.counterName.tmp

PATH=$PATH:$(pwd)
export PATH 

RECUPERATI=$recuperati
export RECUPERATI

recupera_Bl.sh $dir $recuperati $titolo

echo "dir con maggior numero di file: $(cat /tmp/.counterName.tmp)"
echo "numero di elementi recuperati: $(cat /tmp/.count.tmp)"



