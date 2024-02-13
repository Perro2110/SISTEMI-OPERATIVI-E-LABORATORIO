#!/bin/sh
#muoviFile num dirSorgente dirDestinazione ext1 ext2...extN
# CONTROLLO ARGOMENTI

# 4 argomenti
if test $# -le 3;then
    echo "Argomenti insufficenti"
    exit 1
fi 

num=$1
shift



#controllo cartella sorgente
if test -d $1 -a -x $1 ;then
 case "$1" in
        /*) ;;
        *) echo "Errore: $1 deve essere una directory assoluta"
        exit 2;;
    esac
    echo "sorgente esiste ed è una directori $1"
else
    echo "$1 non è una cartella soregnte valida"
    exit 3;
fi

dirSorgente=$1
shift

#Controllo artella di destinazione
if test -d $1 -a -x $1;then
 case "$1" in
        /*) ;;
        *) echo "Errore: $1 deve essere una directory assoluta"
        exit 4;;
    esac
    echo "Destinazione esiste ed è una directori $1"
else
    echo "$1 non è una cartella Destinazione valida"
    exit 5;
fi

dirDestinatario=$1
shift

for i in $*;do
estensione="$i"
case $estensione in
        .*) ;;
        *) echo "Errore: $i esimo argomento deve iniziare con un '.'"
           exit 6;;
esac
done

echo $num
echo $dirSorgente
echo $dirDestinatario


# ESECUZIONE
PATH=$PATH:`pwd` # aggiunge directory script corrente al PATH
export PATH # esporta il PATH


> /tmp/.Counter.tmp
ricercaDiMuovi.sh "$num" "$dirSorgente" "$dirDestinatario" "$*"
echo "*****************************"
echo $(wc -l < /tmp/.Counter.tmp)
echo "******************************"
rm -f /tmp/.Counter.tmp

