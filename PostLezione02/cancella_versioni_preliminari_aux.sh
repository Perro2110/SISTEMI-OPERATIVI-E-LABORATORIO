#!/bin/bash
# Matricola: 184789
#cancella_versioni_preliminari_aux "$dir"

##############################
#### CORE DEL PROGRAMMA : ####
##############################

dir=$1
ext=".txt"
counter=0

echo $dir
cd $dir
echo $(pwd)

for i in $(ls *$ext 2>/dev/null);do
   if test -f $i -a -w $i -a $(head -n 1 < $i|cut -f 3 -d ',') = "preliminare";then # $(grep -c "preliminare" "$i") -ge 1
       counter=$(expr $counter + 1)
       # rm $i
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
            cancella_versioni_preliminari_aux.sh "$dirn"
        fi
done