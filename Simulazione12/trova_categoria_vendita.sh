#!/bin/bash
#184789
# trova _categoria_vendita dir lista_articoli

if test $# -ne 2;then
    echo "numero argomenti non valido"
    exit 1
fi

case $1 in
        /*)
            if test -d $1 -a -x $1;then
                echo "ok"
            else
                echo "cartella Assoluta non trovata o non valida"
                exit 1        
            fi
        ;;
        *) echo "uso: trova _categoria_vendita dir lista_articoli"
                echo "La dir deve essere chiamata con nomi assoluti"
                exit 2;;
esac

dir=$1
shift
lista_articoli=$1
shift

echo " ">$(pwd)/$lista_articoli
echo "0">/tmp/.counter.tmp #count
> /tmp/.counterName.tmp #max 
> /tmp/.LISTA.tmp #max 


LISTA_ARTICOLI=$(pwd)/$lista_articoli
export LISTA_ARTICOLI


PATH=$PATH:$(pwd)
export PATH 

trova_categoria_vendita_bl.sh $dir $lista_articoli

echo "nome della categoria con il maggior numero di articoli venduti $(cat /tmp/.counterName.tmp) con $(cat /tmp/.counter.tmp)"

cat $LISTA_ARTICOLI



