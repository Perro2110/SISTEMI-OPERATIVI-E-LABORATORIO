#!/bin/bash
            ########################################
                        #CONTROLLI VARI
            ########################################
if test $# -ne 2;then
    echo "non è il giusto numero di parametri"
    exit 1
fi
dir="$1"
file="$2"

if test -d $1;then
    # il primo argomento è una directory assoluta?
    case "$dir" in
    /*) ;;
    *) echo "Errore: il primo argomento deve essere una directory assoluta"
    exit 3;;
    esac
else
    echo "primo argomento non è una cartella"
    exit 2
fi
            ########################################
                        #CORE CODE
            ########################################
PATH=$PATH:$(pwd)
export PATH 
if test -x $dir;then
    echo "entrando in $dir"
    cd $dir
    for i in *;do
    if test -d $i;then
        # ricorsione
        trova.sh "$(pwd)"/"$i" "$file"
    else
        if test -f $i;then
            if test $i == $file;then
                echo "trovato qui $(pwd)"
            fi
        fi
    fi
    done
else
    echo "non ho i permessi di entrare.. srry :("
    exit 4
fi
