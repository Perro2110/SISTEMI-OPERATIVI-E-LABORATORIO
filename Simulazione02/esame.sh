#!/bin/bash
#184789
#esame.sh genere tipo anno

if test $# -ne 3;then
    echo "no abbastanza arg"
    exit 3;
fi
genere=$1
tipo=$2
shift
shift

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
anno=$1
echo "__________"
echo "$genere $tipo $anno"

PATH=$PATH:$(pwd)
export PATH 

#Se non esiste $j in $dir ...
if ! test -e $HOME/risultatiFINAL.txt;then
    touch $HOME/risultatiFINAL.txt
else
	echo "">$HOME/risultatiFINAL.txt
fi
DOC=$HOME/risultatiFINAL.txt
export DOC
# creo un file temporaneo per salvare i risultati parziali
echo "0"> /tmp/.counter.tmp
> /tmp/.counterName.tmp

esame_bissnesLogic.sh $genere $tipo $anno


echo "__________________________"
cat $DOC
echo "_________ORDINANDO_______-"
cat $HOME/risultatiFINAL.txt | sort -n

	echo "mese con il maggior numero di titoli di interesse:"
cat /tmp/.counterName.tmp

rm /tmp/.counterName.tmp
rm /tmp/.counter.tmp

