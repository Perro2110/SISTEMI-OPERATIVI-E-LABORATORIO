#!/usr/bin/env sh
# NOME COGNOME NUM_MATRICOLA
read -p "Scrivi il nome del file:" nome
while test $nome != fine; do
if test -e $nome
then
    echo "trovato"
    if test -d $nome
    then
        echo "È na directori"
    fi
    if test -f $nome; then
        echo "FILE exists and is a regular file"
    fi 
else 
    echo "NNtrovato"
fi
read -p "Scrivi il nome del file:" nome
done 