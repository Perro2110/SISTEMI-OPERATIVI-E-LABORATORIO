#!/bin/sh
# cancella_versioni_preliminari dir_articoli 

#dove dir_articoli è un nome relativo di directory.
# CONTROLLO ARGOMENTI

# 1 argomenti
if test $# -ne 1;then
    echo "Argomenti insufficenti"
    exit 1
fi 


#controllo cartella sorgente
if test -d $1 -a -x $1 ;then
case "$1" in
        /*) echo "Errore: $1 deve essere una directory assoluta"
        exit 2;;
        *) ;;
    esac
    echo "sorgente esiste ed è una directori $1"
else
    echo "$1 non è una cartella soregnte valida"
    exit 3;
fi

dirSorgente=$1

echo $dirSorgente


# ESECUZIONE
PATH=$PATH:`pwd` # aggiunge directory script corrente al PATH
export PATH # esporta il PATH


echo "0" > /tmp/max_counter.tmp
> /tmp/countername.tmp
cancella_versioni_preliminari_aux.sh $*

echo "*****************************"
echo $(cat < /tmp/countername.tmp)
echo "******************************"
rm -f /tmp/max_counter.tmp
rm -f /tmp/countername.tmp

