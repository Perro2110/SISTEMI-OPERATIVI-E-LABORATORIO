#!/bin/bash
#184789
#recupera dir recuperati titolo

dir=$1
recuperati=$2
titolo=$3
count=0 #per contare dir con maggior numero di file recuperati
ext=".bak"


echo "_______________________"
echo "dir: $dir"
echo "recuperati: $recuperati"
echo "titolo: $titolo"
echo "_______________________"

cd $dir

for file in $(ls *$ext 2>/dev/null);do  #for i in *.bak
    if test -f $file -a -r $file -a $(head -n 1 $file|grep -c $titolo) -ge 1;then
        cp $file $RECUPERATI
        counter=$(cat /tmp/.count.tmp)
        counter=$(expr $counter + 1)
        echo $counter > /tmp/.count.tmp

        count=$(expr $count + 1)
    fi
done

if test $count -gt  $(cat /tmp/.counter.tmp);then
    echo $count > /tmp/.counter.tmp
    echo $(pwd)> /tmp/.counterName.tmp
fi


## Ricorsione !!
for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
                recupera_Bl.sh $dirn $recuperati $titolo
        fi
done

