#!/bin/bash
if [ "$#" -eq "0" ]
then
    echo "ARGUMENT ERROR: Il faut entrer un argument !"
    echo "Cet argument est un nombre compris entre 3 et 10."
elif [ "$#" -gt "1" ]
then
    echo "ARGUMENT ERROR: Il ne faut rentrer qu'un seul argument !"
    echo "Cet argument est un nombre compris entre 3 et 10."
elif ! [[ ! "$1" =~ [3-9] ]] | [ "$1" -ne "10" ]
then
    echo "ARGUMENT ERROR: L'argument est un nombre compris entre 3 et 10."
else
    echo "$1"
    echo "$1" > ./temp_solveur/src/wsolf.txt
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