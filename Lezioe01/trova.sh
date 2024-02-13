#!/usr/bin/sh
# NOME COGNOME NUM_MATRICOLA
if test $# -eq 2; then 
    # aggiunge directory script corrente al PATH
    PATH=$PATH:$(pwd)
    # esporta il PATH
    export PATH

    directory=$1
    if test -d $directory -a -x $directory; then
    cd $directory
        for i in *
        do
            if test -f $i;then
                if test $i = $2;then 
                    echo "stra gg trovato"
                    exit 1
                fi
            else if test -d $i;then
                echo $i
                trova.sh $(pwd)/$i $2 
            fi
            fi
        done
    else echo "non è una directory"
    fi  
else 
    echo "mancanza di ARGOMENTI" 
    exit 0
fi
