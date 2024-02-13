#!/bin/bash
# Matricola: 184789
#muoviFile num dirSorgente dirDestinazione ext1 ext2...extN

##############################
#### CORE DEL PROGRAMMA : ####
##############################

num=$1
dirSorgente=$2
dirDestinazione=$3
shift
shift 
shift

## Giusto per capire dove sono, lol ##
echo " "
echo "**************************************************"
echo "******************* NEL CODICE *******************"
echo "**************************************************"
echo " "
echo "$num"
echo $dirSorgente
echo $dirDestinazione

cd $dirSorgente

for ext in $*;do
    echo $ext
    # Cerco nella directory i file
    for j in $(ls *$ext 2>/dev/null);do
        if test -f $j -a $(wc -l < $j) -ge $num;then
            echo $j
            echo "Estensione file di tipo $ext di nome $j" >> /tmp/.counter.tmp
            cp "$j" "$dirDestinazione/$j"
        fi
    done
done

## Ricorsione
for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
                ricerca.sh "$num" "$dirn" "$dirDestinazione" $*
        fi
done
