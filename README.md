# **PPII «Projet Pluridisciplinaire d'Informatique Intégrative» 2 - Wordle**


# Informations générales
## Responsable

Olivier Festor <<olivier.festor@telecomnancy.eu>>


## Membres de l'équipe projet
- Quentin LENFANT *(Chef de Projet)* <<quentin.lenfant@telecomnancy.eu>>
- Damien SIMON <<damien.simon@telecomnancy.eu>>
- Paul SANCHEZ *(Secrétaire)* <<paul.sanchez@telecomnancy.eu>>
- Elyas ELAZIZ <<elyas.elaziz@telecomnancy.eu>>


## Description

Ce projet est réalisé dans le cadre du module P2I2 2 - Projet Pluridisciplinaire d'Informatique Intégrative 2 de Première année à TELECOM Nancy.

Il consiste en la création de deux applications autour du jeu Wordle :
- Une application WEB du jeu en Python, HTML, CSS, JavaScript et SQL.
- Un solveur sur terminal où l'ordinateur devine les mots à trouver en fonction des indices donnés par l'utilisateur. Le langage utilisé est le langage C.

[Sujet complet](./Sujet_P2I2_2_Wordle.pdf)


## Conception des applications

[Dossier de conception - Application WEB](./Conception_application_web.pdf)

[Dossier de conception - Solveur](./Conception_solveur.pdf)


## Plannings des tâches (Gantt) du projet

[Planning des tâches (Gantt) - Application WEB](https://docs.google.com/spreadsheets/d/1sz8TemHDO66MD2cEXAMvSilQM0ajqywi5HdHzMRzw44/edit?usp=sharing)
[Planning des tâches (Gantt) - Solveur](https://docs.google.com/spreadsheets/d/1uYkEPePmoIYob3N8ON1gJfrEZKpzgf4EvqCg9EoEarU/edit?usp=sharing)


## Rapport du projet

[Rapport](./Rapport_PPII_2-GroupeE12.pdf)



# Mode d'emploi - Application WEB
## Exécution de l'application
Dans un terminal Linux, une fois le projet cloné, exécuter le script *run.sh* à la racine du projet.
```bash
# À exécuter depuis la racine du projet
bash run.sh
```
Pour fermer l'application, appuyer sur CTRL+C dans le terminal.


## Base de données
La base de données se trouve dans le répertoire *appli/data*.

La structure est décrite dans le fichier *tables.sql* et les données initiales de chaque table dans les fichiers *.csv* correspondants.

Pour la réinitialiser, il faut exécuter les commandes suivantes dans un terminal Linux:
```bash
# Aller dans le répertoire "appli/data" depuis la racine du projet
cd appli/data

# Dans le répertoire "appli/data"
./init_database.sh
```


# Mode d'emploi - Solveur
## Préliminaires
Ce mode d'emploi a été réalisé pour fonctionner sur une distribution Linux.

Le solveur a été programmé en langage C.
Le compilateur utilisé est **clang version 12**. Si vous ne l'avez pas sur votre machine, installez-le:
```bash
# Installation de clang
sudo apt install clang-12
```
Vous pouvez vérifier votre version de clang avec la commande suivante:
```bash
# Version de clang installée
clang --version

# Le résultat de la commande doit être similaire à ce qui suit:
Ubuntu clang version 12.0.1-19ubuntu3
Target: x86_64-pc-linux-gnu
Thread model: posix
InstalledDir: /usr/bin
```

## Exécution de l'application
Choisissez un mot d'une longueur comprise entre 3 et 10 lettres.

Dans un terminal Linux, exécuter le script *solv.sh* à la racine du projet.
```bash
# À exécuter depuis la racine du projet
chmod +x solv.sh
./solv.sh <nombre de lettres>
```
Le paramètre *"nombre de lettres"* est le nombre de lettres du mot que vous voulez faire deviner au solveur. Celui-ci est placé en début de partie dans le fichier **temp_solveur/src/wsolf.txt**

À chaque étape de la partie, le solveur proposera un mot. 

Vous devez lui répondre par une chaîne de caractères de longueur égale à la longueur du mot à trouver et qui contient des 0 et/ou des 1 et/ou des 2.
- Le caractère "0" indique que la lettre correspondante n'est pas dans le mot recherché.
- Le caractère "1" indique que la lettre est dans le mot recherché, mais pas à la bonne place.
- Le caractère "2" indique que la lettre est à la bonne place dans le mot recherché.

La partie se termine lorsque vous renvoyez une chaîne de caractère qui ne contient que des 2.

### Exemple :

Le mot à faire deviner est **BASE**.

À une certaine étape, le solveur propose **BACS**.

Vous lui répondez **2201** ce qui signifie que :
- Le "B" est à la bonne place,
- Le "A" est à la bonne place,
- Le "C" n'est pas dans le mot à trouver,
- Le "S" est dans le mot à trouver, mais pas à la bonne place.

À l'étape suivante, le solveur propose **BASE**.
Vous renvoyez alors la chaîne **2222** ce qui terminera la partie.

<!-- Pour fermer le solveur en cours de partie, appuyer sur CTRL+C dans le terminal. -->

## Exécution des tests des structures
Dans un terminal Linux, allez dans les fichiers du solveur :
```bash
# À exécuter depuis la racine du projet
cd solveur/
```
Puis choisissez la structure que vous voulez tester en tapant la commande correspondante :
```bash
make tree       # Exécution des tests sur la structure d'arbre
make table      # Exécution des tests sur la structure de table d'occurrence
make dic        # Exécution des tests sur la structure de dictionnaire
```
Les fichiers source des tests sont dans le répertoire **src/**:
```bash
src/dictionnary_test.c      # Dictionnaire
src/test_table_occ.c        # Table d'occurrence
src/test_tree               # Arbre
```

## Suppression des fichiers ".o" et ".exe" générés
Lors de la compilation, les fichiers objet **.o** et les exécutables **.exe** ont été générés respectivement dans les répertoires **temp_solveur/obj** et **temp_solveur/exe**.

Pour les supprimer, dans un terminal Linux, exécutez les commandes suivantes à la racine du projet :
```bash
# À exécuter depuis la racine du projet
cd solveur/
make clean
```
