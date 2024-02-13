#!/bin/bash
#184789
##############  controlli  ##############
#identifica dir messaggio

if test $# -ne 2;then
    echo "errore numero di argomenti non conforme"
    exit 1
fi

case $1 in
        /*)
            echo "uso: identifica.sh dir messaggio"
                echo "La dir deve essere chiamata con nomi relativi"
                exit 2
        ;;
        *)  if test -d $1 -a -x $1;then
                echo "ok"
            else
                echo "cartella Relativa non trovata o non valida"
                exit 2       
            fi
        ;;
esac
dir=$1
shift
messaggio=$1
shift
echo "$dir $messaggio"

> "$dir/Trovatii"
> "$dir/Max"

# la directory dir e' relativo alla directory corrente
export TROVATI="`pwd`/$dir/Trovatii"
export MAX="`pwd`/$dir/Max"

echo "0"> /tmp/.counter.tmp

PATH=$PATH:$(pwd)
export PATH 

identifica_bisness_logic.sh $(pwd)/$dir $messaggio
echo "____________"
echo $(sort -n -r $TROVATI | head -n 5 |cut -f 2 -d ' ')
echo "____________"

echo "$(cat $MAX)"




