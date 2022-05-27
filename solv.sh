#!/bin/bash
if [ "$#" -eq "0" ]
then
    echo "ARGUMENT ERROR: Il faut entrer un argument !"
    echo "Cet argument est un nombre compris entre 3 et 20."
elif [ "$#" -gt "1" ]
then
    echo "ARGUMENT ERROR: Il ne faut rentrer qu'un seul argument !"
    echo "Cet argument est un nombre compris entre 3 et 20."
elif [ "$1" -lt "3" ] || [ "$1" -gt "20" ]
then
    echo "ARGUMENT ERROR: L'argument est un nombre compris entre 3 et 20."
else
    echo $1 > ./temp_solveur/src/wsolf.txt
    cd ./temp_solveur/
    if [ ! -e ./obj/ ]
    then
    mkdir ./obj/
    fi
    if [ ! -e ./exe/ ]
    then
    mkdir ./exe/
    fi
fi
make main
