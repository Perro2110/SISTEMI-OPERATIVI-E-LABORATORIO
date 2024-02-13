#!/bin/bash
#184789
# esame_bissnesLogic.sh $genere $tipo $anno
echo "__________ARG IN Bisness logic__________"

genere=$1
tipo=$2
anno=$3
shift 
shift
shift
count=0
ext=".txt"
cd $anno
echo "$genere $tipo $anno"
echo "__________Bisness logic__________"

for file in $(ls *$ext 2>/dev/null);do  #for file in *.txt
    if test -f $file -a -r $file;then
        arr=$(grep $genere $file|grep $tipo $file|cut -d ',' -f 1,3,6)
        echo $arr
        count=$(grep  $genere $file|grep -c $tipo $file)
        echo $arr>>$DOC
        if test $count -gt $(cat /tmp/.counter.tmp);then
                echo $count > /tmp/.counter.tmp
                echo $file > /tmp/.counterName.tmp
        fi
    fi
done

for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
                esame_bissnesLogic.sh $genere $tipo $dirn
        fi
done

