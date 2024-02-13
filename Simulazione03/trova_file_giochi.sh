#!/bin/bash
#184789
#trova_file_giochi dir

#controllo numero di argomenti
if test $# -ne 1;then
    echo "errore numero argomenti"
    exit 1
fi

#controllo se dir non è assoluta 
#OBBLIGO CHE IN ARG1 CI SIA UN nome relativo di cartella

case $1 in
        /*)
             echo "Richiesta cartella con percorso relativo no Assoluto"
                exit 2    
        ;;
        *) if test -d $1 -a -x $1;then
            echo "ok"
           else
            echo "cartella non valida o non trovata"
            exit 2
            fi
        ;;
esac

dir=$1
shift

#Se non esiste $j in $dir ...
if ! test -e $HOME/"trovato.txt";then
    touch $HOME/"trovato.txt"
else
	echo "pronto alla scrittura"
fi

echo "0"> /tmp/.counter.tmp
> /tmp/.counterNome.tmp

PATH=$PATH:$(pwd)
export PATH 

trova_file_giochi_bisnessLogic.sh $(pwd)/$dir
echo "Risultato dell ricerca:"
cat /tmp/.counterNome.tmp

rm /tmp/.counter.tmp
rm /tmp/.counterNome.tmp

