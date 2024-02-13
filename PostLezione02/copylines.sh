#!/bin/bash
# copylines nome_dir_assoluto stringa nomefile1 nomefile2 ... nomefileN

################################
#     CONTROLLO ARGOMENTI      #
################################
if test $# -lt 3;then
    echo "error: troppi pochi comandi"
    exit 1
else 
    echo ok
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
        *) echo "uso: copylines nome_dir_assoluto stringa nomefile1 nomefile2 ... nomefileN"
                echo "La dir deve essere chiamata con nomi assoluti"
                exit 2;;
esac
nome_dir_assoluto=$1
shift

stringa=$1
shift

for i in $*;do
    #OBBLIGO CHE IN ARG3 ... ecc (ora agr1) CI SIA UNa stringa
    case $i in
            *[!a-z]*) echo "uso: copylines nome_dir_assoluto stringa nomefile1 nomefile2 ... nomefileN"
                    echo "nomefile $i deve essere una stringa di soli valori alfabetici minuscoli!!"
                    exit 4;;
    esac
done

echo "________Argmenti passati (per debug)"
echo $nome_dir_assoluto
echo $stringa
echo $*
echo "____________________________________"


PATH=$PATH:$(pwd)
export PATH 

echo "0" > /tmp/.counterFileSpostati.tmp
> /tmp/.counterStringhe.tmp


while true
do
    cpylinesBis.sh $nome_dir_assoluto $stringa $* 
        if test $(cat /tmp/.counterFileSpostati.tmp) -eq 0;then
            sleep `expr 60 \* 60`
        else
             cat /tmp/.counterFileSpostati.tmp
             cat /tmp/.counterStringhe.tmp
             rm /tmp/.counterFileSpostati.tmp
             rm /tmp/.counterStringhe.tmp
             exit 0
    fi
done















