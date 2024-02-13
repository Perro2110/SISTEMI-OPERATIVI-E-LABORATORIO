#!/bin/bash
#184789
#trova_fornitori_migliori dir cod_parte num


dir=$1
cod_parte=$2
num=$3
ext=".txt"
echo "arrivati:__________"
echo "dir: $dir"
echo "cod_parte: $cod_parte"
echo "num:$num"
echo "___________________"

cd $dir

for file in $(ls *$ext 2>/dev/null);do  #for i in *.txt
    if test -f $file -a -r $file -a $(grep -c $cod_parte $file) -ge 1 ;then
    a=$(grep $cod_parte $file | cut -d ',' -f 4) 
        if test $a -gt $num;then
            max=$(cat /tmp/.counter.tmp)
            echo "qua:: $max"
            val=$(grep $cod_parte $file | cut -d ',' -f 4 )
            echo "qui:: $val"
            if test $val -ge $max;then
                echo $val > /tmp/.counter.tmp
                echo $(grep $cod_parte $file | cut -d ',' -f 1 ) > /tmp/.counterName.tmp
            fi
        fi
    fi
done

for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
                trova_fornitori_migliori_bl.sh $dirn $cod_parte $num
        fi
done

#    1          2        3      4
# nome_forn,cod_part,nome_part,num