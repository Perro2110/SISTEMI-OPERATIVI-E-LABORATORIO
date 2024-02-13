#!/bin/bash
#Marco Perrotta 184789
#Interfaccia: esame genere tipo anno

if test $# -ne 3;then
    echo "numero argomenti non valido"
    exit 1
fi
genere=$1
tipo=$2
shift 
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
        *) echo "uso: esame genere tipo anno"
                echo "La dir deve essere chiamata con nomi assoluti"
                exit 2;;
esac 
anno=$1
shift

echo "inseriti:____________"
echo "$genere $tipo $anno"
echo "_____________________"

echo "">$HOME/risultati

# creazione file temporanei per salvare i risultati parziali
echo "0"> /tmp/.counter.tmp
> /tmp/.counterName.tmp

RISULTATI=$HOME/risultati
export RISULTATI 

PATH=$PATH:$(pwd)
export PATH 

esame_BisnessLogic.sh $genere $tipo $anno

sort -n -r $RISULTATI | cat

echo "Il mese col maggior numero è: $(cat /tmp/.counterName.tmp) con ben $(cat /tmp/.counter.tmp) numero Titoli coerenti"

