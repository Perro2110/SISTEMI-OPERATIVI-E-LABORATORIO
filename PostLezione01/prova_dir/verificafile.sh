#!/usr/bin/env sh
# Marco Perrotta 
echo "inserisci nome"
read nome
while test $nome != "fine";do
    if test -d $nome;then
        echo "file esiste ed è una directory"
    elif test -f $nome;then
        echo "file esiste ed è un file"
    else 
        echo "file non esiste"
    fi    
    echo "inserisci nome"
    read nome
done

