#!/bin/sh
# cancella_versioni_preliminari:aux dir_articoli 

#dove dir_articoli è un nome relativo di directory.
# CONTROLLO ARGOMENTI


dirSorgente=$1

echo $dirSorgente
#entrare nella directory
cd $dirSorgente
#inizializzazione a 0 di una variabile contatore counter
counter=0
ext=".txt"

    for i in $(ls *$ext 2>/dev/null)
    do
        echo "i: $i"
        if test -w "$i";then
            echo "a"
            if test $(head -n 1 < $i|cut -f 3 -d ',') = "preliminare";then
                echo "preliminare"
                #rm -f $i
                counter=$(expr $counter + 1)
            fi
        fi
done
val=$(cat /tmp/max_counter.tmp)
echo $val
if test $counter -gt $val;then
    echo $(pwd) > /tmp/countername.tmp
    echo $counter >/tmp/max_counter.tmp
fi

for dirn in *
do
echo i;
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn";then
                cancella_versioni_preliminari_aux.sh $dirn
        fi
done


