#!/bin/bash
#184789
#trova_script_Bl dir

dir=$1
ext=".sh"
string="#!/bin/bash"
c=0
echo ":::::::::::::"
echo "arrivato $dir"
echo ":::::::::::::"

cd $dir

for file in $(ls *$ext 2>/dev/null);do  #for i in *.sh
    if test -f $file -a -r $file -a -w $file -a $(grep -c $string $file) -ge 1;then
        echo $file >> $SCRIPT
        c=$(expr $c + 1) #aumenta il count se c'è 
    fi
done

if test $c -gt $(cat /tmp/.counter.tmp);then
    echo $c > /tmp/.counter.tmp
    echo $(pwd)>/tmp/.counterName.tmp
fi

## Ricorsione
for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
                trova_script_Bl.sh $dirn
        fi
done