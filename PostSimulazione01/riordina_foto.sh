#!/bin/bash
# riordina_foto dir_sorgente dir_destinazione
if test $# -ne 2;then
    echo "sei gay"
fi

case $1 in
        /*)
            echo "Errore dir_sorgente non deve essere chiamata con un percorso assoluto ma relativo"
            exit 1
        ;;
        *)  if test -d $1 -a -x $1;then
                echo "ok"
            else
                echo "cartella relativa non trovata o non valida"
                exit 2        
            fi;
esac
dir_sorgente=$1
shift

case $1 in
        /*)
            echo "Errore dir_destinazione non deve essere chiamata con un percorso assoluto ma relativo"
            exit 1
        ;;
        *)  if test -d $1 -a -x $1;then
                echo "ok"
            else
                echo "cartella relativa non trovata o non valida"
                exit 2        
            fi;
esac
dir_destinazione=$1
shift

echo "________________________"
echo " $dir_sorgente  $dir_destinazione "
echo "________________________"

if ! test -e $dir_destinazione/duplicati;then
    mkdir $dir_destinazione/duplicati
fi

>/tmp/.Namecounter.tmp
>/tmp/.NamecounterRep.tmp

PATH=$PATH:$(pwd)
export PATH 


riordina_foto_esec.sh "$dir_sorgente" "$(pwd)/$dir_destinazione"

##bisness logic finale
wc -l /tmp/.Namecounter.tmp
echo "_______________________________________-"
cat /tmp/.Namecounter.tmp

rm /tmp/.Namecounter.tmp
rm /tmp/.NamecounterRep.tmp