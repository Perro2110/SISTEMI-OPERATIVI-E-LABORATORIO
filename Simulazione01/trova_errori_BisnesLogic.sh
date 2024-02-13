#!/bin/bash
#trova_errori_BisnesLogic.sh dir

dir=$1
echo "..........................."
echo $dir
echo "..........................."



## Ricorsione
for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
                trova_errori_BisnesLogic.sh $dirn
        fi
done