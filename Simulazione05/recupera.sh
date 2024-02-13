##!/bin/bash
#184789
#recupera.sh dir recuperati titolo
if test $# -ne 3;then
    echo "numero argomenti non valido"
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
        *) echo "uso: recupera.sh dir recuperati titolo"
                echo "La dir deve essere chiamata con nomi assoluti"
                exit 2;;
esac
dir=$1
shift

recuperati=$1
shift
case $recuperati in
        /*)
            if ! test -e $recuperati -a -d $recuperati;then
                if test -e $recuperati -a -f $recuperati;then
                    rm $recuperati
                fi
                mkdir $recuperati
                echo "ok"
            else 
                echo "DIR GIA' ESISTENTE ma ok"
            fi
        ;;
        *) echo "uso: recupera.sh dir recuperati titolo"
                echo "La dir deve essere chiamata con nomi assoluti"
                exit 2;;
esac

titolo=$1

echo "passati: __________"
echo "$dir $recuperati $titolo"
echo "____________________"


echo "0"> /tmp/.counterSERIO.tmp
echo "0"> /tmp/.counter.tmp
> /tmp/.counterName.tmp

PATH=$PATH:$(pwd)
export PATH 

recupera_bisness_Logic.sh $dir $recuperati $titolo

cat /tmp/.counterName.tmp
cat /tmp/.counterSERIO.tmp





