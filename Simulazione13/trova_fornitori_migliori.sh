#!/bin/bash
#184789
#trova_fornitori_migliori dir cod_parte num
if test $# -ne 3;then
    echo "numero di argomenti non valido"
    exit 1
fi

#OBBLIGO CHE IN ARG1 CI SIA UN nome assoluto di cartella
case $1 in
        /*)
            if test -d $1 -a -x $1;then
                echo "ok"
            else
                echo "cartella Assoluta non trovata o non valida"
                exit 1        
            fi
        ;;
        *) echo "uso: trova_fornitori_migliori dir cod_parte num"
                echo "La dir deve essere chiamata con nomi assoluti"
                exit 2;;
esac

dir=$1
shift

cod_parte=$1
shift


#OBBLIGO CHE IN ARG1 CI SIA UN NUMERO
case $1 in
        *[!0-9]*) echo "uso: trova_fornitori_migliori dir cod_parte num"
                echo "num deve essere un numero"
                exit 2;;
esac

num=$1

echo "0"> /tmp/.counter.tmp
> /tmp/.counterName.tmp


PATH=$PATH:$(pwd)
export PATH 

trova_fornitori_migliori_bl.sh $dir $cod_parte $num

echo "fornitore con maggior numero è: $(cat /tmp/.counterName.tmp) con $(cat /tmp/.counter.tmp) pezzi"