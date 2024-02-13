#recupera.sh dir recuperati titolo
dir=$1
recuperati=$2
titolo=$3
c=0
ext=".bak"
echo "passati: __________"
echo "$dir"
echo "$recuperati"
echo " $titolo"
echo "____________________"

cd $dir

for file in $(ls *$ext 2>/dev/null);do  #for i in *.bkt
    if test -f $file -a -r $file -a $(head -n 1 <$file|grep -c $titolo) -ge 1;then
        cp $file $recuperati
        c=$(expr $c + 1)
    fi
done

cs=$(cat /tmp/.counterSERIO.tmp)
cs=$(expr $c + $cs)
echo $cs>/tmp/.counterSERIO.tmp

cs=$(cat /tmp/.counter.tmp)
if test $c -gt $cs;then
    echo $c>/tmp/.counter.tmp
    echo $(pwd)>/tmp/.counterName.tmp
fi

## Ricorsione
for dirn in *
do
        # controllando il permesso di esecuzione evito loop 
        if test -d "$dirn" -a -x "$dirn"
        then
                recupera_bisness_Logic.sh $dirn $recuperati $titolo
        fi
done



