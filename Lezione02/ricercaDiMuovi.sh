#!/bin/sh
#muoviFile num dirSorgente dirDestinazione ext1 ext2...extN


num="$1"
dir1="$2"
dir2="$3"

shift 
shift
shift

cd "$dir1"

for ext in $*
do
# cerca file
    for i in $(ls *$ext 2>/dev/null)
    do
            echo i $i
            if test -f "$i" -a $(wc -l < $i) -ge $num;then
                    cp "$i" "$dir2$i"
                    echo "Copia di $i" >> /tmp/.Counter.tmp

            fi
    done
done
# ricerca ricorsiva
for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
                ricercaDiMuovi.sh "$num" "$dirn" "$dir2" $*
        fi
done

