#!/bin/bash
#cercaFile stringa dir num
# Matricola: 184789


##############################
#### CORE DEL PROGRAMMA : ####
##############################

stringa=$1
dir=$2
num=$3
ext=".txt"
counter=0

echo "______________________"
echo $dir
echo "______________________"

cd $dir

    # Cerco nella directory i file con l'estensione che voglio
for i in $(ls *$ext 2>/dev/null);do
echo i: $i
    if test -f $i -a -r $i -a $(grep -c $stringa "$i") -ge $num;then
            echo $i
            counter=$(expr $counter + 1)
    fi
done
echo $counter
if test $counter -ge $(cat /tmp/.counter.tmp);then
    echo $counter > /tmp/.counter.tmp
    echo $(pwd) > /tmp/.counterName.tmp
fi

## Ricorsione
for dirn in *;do
        # controllando il permesso di esecuzione evito loop   cercaFile stringa dir num
        if test -d "$dirn" -a -x "$dirn"
        then
                cercaStringa.sh "$stringa" "$dirn" "$num"
        fi
done

 