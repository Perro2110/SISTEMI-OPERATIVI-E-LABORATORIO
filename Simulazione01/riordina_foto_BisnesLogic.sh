#!/bin/bash

#riordina_foto dir_sorgente dir_destinazione

dir_sorgente=$1
dir_destinazione=$2
ext=".JPG"

echo "******************************"
echo "$dir_sorgente $dir_destinazione $ext"
echo "******************************"

cd $dir_sorgente

    # Cerco nella directory i file .$ext
    for j in $(ls *$ext 2>/dev/null);do
       if test -r $j;then
            if ! test -e $dir_destinazione/$j;then
                mv $j $dir_destinazione/$j
            else
                echo $j>>/tmp/.fileDuplicati.tmp            #//
                n=$(grep -c $j /tmp/.fileDuplicati.tmp)   #// A CASA GUARDARE SUA RISOLUZIONE
                echo $n
                mv $j $dir_destinazione/duplicati/$j$n     #//
            fi
       fi
	done


for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
                riordina_foto_BisnesLogic.sh $dirn $dir_destinazione
        fi
done