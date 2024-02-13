#!/bin/bash
#184789
#trova_file_giochi dir

dir=$1
ext=".txt"
count=0
echo "*************"
echo "   $dir      "
echo "*************"
cd $dir
for file in $(ls *$ext 2>/dev/null);do  #for i in *.txt
    if test -f $file -a -r $file -a $(head -n 1 $file|grep -c "giochi") -ge 1;then
        count=$(wc -l $file|cut -d ' ' -f 1)
        echo "count per debugg : $count"

        f=$(cat /tmp/.counter.tmp)
        if test $count -ge $f;then
            echo $count  > /tmp/.counter.tmp
            echo $file > /tmp/.counterNome.tmp
        fi
        echo $(pwd)/$file >> $HOME/"trovato.txt"
    fi
done

for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
                trova_file_giochi_bisnessLogic.sh $dirn
        fi
done
