#!/bin/bash
 #copylinesBis $nome_dir_assoluto $stringa $* 

nome_dir_assoluto=$1
stringa=$2
shift
shift
counter=0
cd $nome_dir_assoluto

for elementoInCartella in $*;do #per tutti gli elementi nella cartella
        if test -f $elementoInCartella -a -r $elementoInCartella;then
            if test $(grep -c $stringa $elementoInCartella) -ge 0;then
                counter=$(expr $counter + 1)
                echo $(grep $stringa $elementoInCartella)>> /tmp/.counterStringhe.tmp
                # mv $$elementoInCartella /tmp
            fi
        fi
done

val=$(cat /tmp/.counterFileSpostati.tmp)
counter=$(expr $counter + $val)
echo $counter > /tmp/.counterFileSpostati.tmp

for dirn in *;do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn";then
                cpylinesBis.sh $dirn $stringa $* 
        fi
done

