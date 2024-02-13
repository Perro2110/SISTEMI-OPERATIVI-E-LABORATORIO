#!/bin/bash
# trova_errori.sh dir
dir=$1
ext=".log"
shift
c="0"
echo ____________________
echo $dir
echo ____________________

cd $dir

for file in $(ls *$ext 2>/dev/null);do  #for i in *.log
    if test -f $file -a -r $file;then
                if test $(grep -c "error" "$file") -ge 0;then
		        c=$(expr $c + 1) #aumenta il count se c'è 
                        echo "********$c**********"
                fi
		grep "error" $file | cut -d ',' -f 1,2,6 >> $ERRORI  # "SE C'E' scritto error" prendi la 1° 2° 3° riga delimitati da una ,
		grep "warning" $file | cut -d ',' -f 1,2,6 >> $WARNING #poi mettili in $...
    fi
done
echo pollo
eg=$(cat /tmp/.counter.tmp)
echo ___________
echo "salvato: $eg"
echo "attuale: $c"
echo ___________
if test $eg -le $c; then
    echo "...........$c........."
    echo $c > /tmp/.counter.tmp
    echo "...... $(cat /tmp/.counter.tmp) .........."
    echo $(pwd)>/tmp/.MaxcounterDIR.tmp
fi

for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
                trova_errori_esec.sh $dirn
        fi
done

