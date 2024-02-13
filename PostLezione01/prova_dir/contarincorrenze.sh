if test $# -lt 2;then
    echo "dati insufficenti"
    exit 1
fi
if test -e $1;then
    file=$1
    shift
    echo "file trovato..."
    for i in $*;do
        a=$(grep $i $file |wc -l)
        echo "trovate n: $a di $i" 
    done
else
    echo "Immetere dati validi"
    exit 2
fi
