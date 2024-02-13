#!/bin/bash
#184789
#esame nome anno


nome=$1
anno=$2
ext=".txt"
echo "passati:_________"
echo "nome: $nome Dir_anno: $anno"
echo "__________________"

cd $anno

for file in $(ls *$ext 2>/dev/null);do  #for i in *.txt
    if test -f $file -a -r $file -a $(grep -c $nome "$file") -ge 1;then
		grep $nome $file | cut -d ',' -f 1,3,4 >> $FIUMILOG  # "SE C'E' scritto error" prendi la 1° 2° 3° colonna delimitati da una ,
        a=$(grep $nome $file | cut -d ',' -f 1)
        echo "a: $a"
        min=$(cat /tmp/.counter.tmp)
        echo "min: $min "
        if test $a -lt $min;then
            echo "dentro__________________"
            echo $a > /tmp/.counter.tmp
            echo $file > /tmp/.counterName.tmp
        fi 
    fi
done

for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
            esame_bisness_logic.sh $nome $dirn
        fi
done
