#!/bin/bash
#184789
##############  controlli  ##############
#identifica dir messaggio

dir=$1
messaggio=$2
echo "$dir $messaggio"
ext=".txt"

cd $dir

for file in *;do
    if test -f $file -a -r $file -a $(grep -c $messaggio "$file") -ge 1;then
        c=$(grep -c $messaggio "$file")
        echo "$c $file">>$TROVATI
        echo ".................."
        cat $TROVATI
        echo ".................."
        cc=$(cat /tmp/.counter.tmp)
        if test $c -gt $cc;then
            echo $c>/tmp/.counter.tmp
            echo $(pwd)/$file>$MAX
        fi 
    fi
done


## Ricorsione
for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
                identifica_bisness_logic.sh $dirn $messaggio
        fi
done
