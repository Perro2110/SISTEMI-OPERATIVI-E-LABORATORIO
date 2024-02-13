#!/bin/bash
#Marco Perrotta 184789
#Interfaccia: esame genere tipo anno
genere=$1
tipo=$2
anno=$3
ext=".txt"
shift
shift
shift

echo "BisnessLogic______"
echo "Arrivati: genere: $genere tipo: $tipo anno: $anno"

cd $anno

for file in $(ls *$ext 2>/dev/null);do  #for i in *.txt
    if test -f $file -a -r $file;then
        a=$(grep $tipo $file | grep $genere|cut -d ' ' -f 1,3,6)
        echo $a >>$RISULTATI
        vM=$(grep $tipo $file | grep -c $genere)
        max=$(cat /tmp/.counter.tmp)
        if test $vM -gt $max;then
            echo $vM > /tmp/.counter.tmp
            echo "$(pwd)/$file" > /tmp/.counterName.tmp
        fi 
	fi
done

## Ricorsione
for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
            esame_BisnessLogic.sh $genere $tipo $dirn
        fi
done
