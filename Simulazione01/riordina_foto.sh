#!/bin/bash
#riordina_foto dir_sorgente dir_destinazione

#controllo parametri passati
if test $# -ne 2;then
    echo "Numero di argomenti non coincidente"
    exit 1
fi

case $1 in
        /*)
            if test -d $1 -a -x $1;then
                echo "cartella Assoluta non path relativo"
                exit 2  
            else
                echo "non valida"
                exit 3        
            fi
        ;;
        *)             
            if test -d $1 -a -x $1;then
                echo "ok"
            else
                echo "non valida"
                exit 3        
            fi
esac
dir_sorgente=$1
shift 

case $1 in
        /*)
            if test -d $1 -a -x $1;then
                echo "cartella Assoluta non path relativo"
                exit 2  
            else
                echo "non valida"
                exit 3        
            fi
        ;;
        *)             
            if test -d $1 -a -x $1;then
                echo "ok"
            else
                echo "non valida"
                exit 3        
            fi
esac
dir_destinazione=$1
shift 
for file in *;do
if ! test -e $dir_destinazione/duplicati;then
        mkdir $dir_destinazione/duplicati
fi
done
echo "passati: $dir_sorgente e $dir_destinazione"
> /tmp/.fileDuplicati.tmp



PATH=$PATH:$(pwd)
export PATH 

# ricorsione facendolo partire su cartella $i con argomento $file
wc -l /tmp/.fileDuplicati.tmp
riordina_foto_BisnesLogic.sh $(pwd)/$dir_sorgente $(pwd)/$dir_destinazione
ls $dir_destinazione

rm /tmp/.fileDuplicati.tmp