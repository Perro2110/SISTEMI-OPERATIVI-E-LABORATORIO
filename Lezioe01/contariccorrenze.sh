#!/usr/bin/env sh
# NOME COGNOME NUM_MATRICOLA
conta=0
if test $# -gt 1; then 
    file=$1
    shift
    if test -f $file ; then
        echo "FILE trovato"
        for i in $*
        do
        #if test $i != $1  # potevo fare lo shift
        #then
            conta=$(grep -c $i $file)
            echo "parametro $i : $conta"
        #fi 
        done
    else echo "non è un file"
    fi  
else 
    echo "mancanza di ARGOMENTI" 
    exit 0
fi
