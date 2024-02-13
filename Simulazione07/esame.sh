#!/bin/bash
#184789
#esame nome anno

if test $# -ne 2;then
    echo "errore in numero parametri"
    exit 1
fi

#non presumendo controlli su fiume essendo che puo avere numeri ?
nome=$1
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
        *) echo "uso: esame nome anno"
                echo "La dir deve essere chiamata con nomi assoluti"
                exit 2;;
esac
anno=$1

echo "">$HOME/fiumilog.txt

FIUMILOG=$HOME/fiumilog.txt
export FIUMILOG 

echo "1000"> /tmp/.counter.tmp
> /tmp/.counterName.tmp

PATH=$PATH:$(pwd)
export PATH 

esame_bisness_logic.sh $nome $anno

echo "Il minimo è stato riscontrato il giorno: `cat /tmp/.counterName.tmp`"
echo "Livello minimo riscontrato: `cat  /tmp/.counter.tmp` metri"

echo "LOG: __________________________"
cat $FIUMILOG



