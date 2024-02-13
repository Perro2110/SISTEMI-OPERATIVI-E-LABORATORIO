#!/bin/bash
#184789
#cerca_misure_bl.sh $dir $header
dir=$1
header=$2
ext=".log"
counter=0
echo "_______________  "
echo " $dir e $header  "
echo "_________________"

cd $dir


for file in $(ls *$ext 2>/dev/null);do  #for i in *.log
    if test -f $file -a -r $file -a -w $file -a $(head -n 1 $file|grep -c $header) -ge 1;then
        echo "$(pwd)/$file" >> $MISURE
        counter=$(expr $counter + 1)
    fi
done

if test $counter -gt $(cat /tmp/.counter.tmp);then
    echo $counter > /tmp/.counter.tmp
    echo $(pwd) > /tmp/.counterName.tmp
fi

## Ricorsione !!
for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
                cerca_misure_bl.sh $dirn $header
        fi
done