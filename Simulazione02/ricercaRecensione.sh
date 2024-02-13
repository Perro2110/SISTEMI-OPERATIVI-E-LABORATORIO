#!/bin/bash

cd $1

for i in `ls *.txt 2>/dev/null`
do
    if [ -f $i -a -r $i ]; then
        `grep $2 $i | grep $3 $i | cut -d ',' -f 1,3,6` >> $HOME/risultati.txt
        if [ `grep $2 $i | grep $3 $i | wc -l` -ge `cat /tmp/.righe.tmp` ]; then
            `grep $2 $i | grep $3 $i | wc -l` > /tmp/.righe.tmp
            $i > /tmp/.meseMigliore.tmp
    fi
done

for i in *
do
    if [ -d $i -a -x $i ]; then
        ricercaRecensione.sh `pwd`/$i $2 $3
    fi
done