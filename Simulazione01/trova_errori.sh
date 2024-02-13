#!/bin/bash
#trova_errori.sh dir

if test $# -ne 1;then
    echo "Numero di argomenti non coincidente"
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
        *) echo "uso: nomeCommand arg1 ... argN"
                echo "La dir deve essere chiamata con nomi assoluti"
                exit 2;;
esac
dir=$1
shift

errori="$HOME/errori.txt"
export errori

warning="$HOME/warning.txt"
export warning


echo "passati: $dir"

>/tmp/.Mag.tmp
echo "0"> /tmp/.Num.tmp

PATH=$PATH:$(pwd)
export PATH 

trova_errori_BisnesLogic.sh $dir

echo $(cat /tmp/.Mag.tmp)

rm  /tmp/.Mag.tmp
rm  /tmp/.Num.tmp