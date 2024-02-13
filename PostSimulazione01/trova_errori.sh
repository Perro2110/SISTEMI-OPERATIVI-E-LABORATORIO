#!/bin/bash
# trova_errori.sh dir
if test $# -ne 1;then
    echo "numero argomenti errato"
    exit 1
fi
 
 #OBBLIGO CHE IN ARG1 CI SIA UN nome assoluto di cartella
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

ERRORI=$HOME/errori.txt 
WARNING=$HOME/warning.txt

PATH=$PATH:$(pwd)

export ERRORI
export WARNING
export PATH 

echo "0">/tmp/.counter.tmp
> /tmp/.MaxcounterDIR.tmp

trova_errori_esec.sh $dir

cat /tmp/.MaxcounterDIR.tmp
rm /tmp/.MaxcounterDIR.tmp
