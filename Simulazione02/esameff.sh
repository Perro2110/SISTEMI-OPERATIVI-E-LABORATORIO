#!/bin/bash

if [ $# -ne 3]; then
    echo "Numero degli argomenti errati"
    exit 3
fi
echo $3

PATH=$PATH:`pwd`
export PATH

> $HOME/risultati.txt
touch /tmp/.meseMigliore.tmp
touch /tmp/.righe.tmp

ricercaRecensione.sh $3 $1 $2

rm /tmp/.righe.tmp
sort -g -r $HOME/risultati.txt
echo $(cat /tmp/.meseMigliore.tmp | cut -d '.' -f 1)
rm /tmp/.meseMigliore.tmp
