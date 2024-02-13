#!/bin/bash
# riordina_foto dir_sorgente dir_destinazione

dir_sorgente=$1
dir_destinazione=$2
ext=".JPG"
shift
shift

echo "****************"
echo "$dir_sorgente $dir_destinazione"
echo "*****************"

cd $dir_sorgente

# Cerco nella directory i file .$ext
for file in $(ls *$ext 2>/dev/null);do  #for i in *.JPG
    if ! test -e $dir_destinazione/$file;then
        mv $file $dir_destinazione  
        echo $file >> /tmp/.Namecounter.tmp
        echo $file >> /tmp/.NamecounterRep.tmp
    else
        c=$(grep -c $file /tmp/.NamecounterRep.tmp)
        mv $file $dir_destinazione/duplicati/$file$c
        echo $file >> /tmp/.NamecounterRep.tmp
    fi
done

############################################################################

## Ricorsione
for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
            riordina_foto_esec.sh "$dirn" "$dir_destinazione"
        fi
done

