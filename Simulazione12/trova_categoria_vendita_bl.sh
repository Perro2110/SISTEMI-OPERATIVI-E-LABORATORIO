#!/bin/bash
#184789

# trova _categoria_vendita dir lista_articoli

dir=$1
lista_articoli=$2
ext=".log"
c=0

echo "passati:________________"
echo "$dir $lista_articoli"
echo "_________________________" 

cd $dir
echo "">/tmp/.LISTA.tmp

for file in $(ls *$ext 2>/dev/null);do  #for i in *.log
    if test -f $file -a -r $file -a $(head -n 1 $file|cut -f 5 -d ','|grep -c "venduto") -ge 1;then
           c=$(expr $c + 1)
           echo "$(head -n 1 $file)">>/tmp/.LISTA.tmp
    fi
done

if test $c -gt $(cat /tmp/.counter.tmp);then
    echo $c > /tmp/.counter.tmp
    echo $(pwd)>/tmp/.counterName.tmp 
    cat /tmp/.LISTA.tmp>$LISTA_ARTICOLI
fi

for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
            trova_categoria_vendita_bl.sh $dirn $lista_articoli
        fi
done

