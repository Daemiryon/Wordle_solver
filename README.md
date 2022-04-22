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
- Une application WEB du jeu en Python/WEB/BD
- Un solveur sur terminal où l'ordinateur devine les mots à trouver en fonction des indices donnés par l'utilisateur. Le langage utilisé est le langage C.

[Sujet complet](./Sujet_P2I2_2_Wordle.pdf)


## Conception des applications

[Dossier de conception - Application WEB](./Conception_application_web.pdf)

[Dossier de conception - Solveur (Non disponible)](./)


## Plannings des tâches (Gantt) du projet

[Planning des tâches (Gantt) - Application WEB](https://docs.google.com/spreadsheets/d/1sz8TemHDO66MD2cEXAMvSilQM0ajqywi5HdHzMRzw44/edit?usp=sharing)


## Rapport du projet

[Rapport (Non disponible)](./)



# Mode d'emploi - Application WEB
## Execution de l'application
Dans un terminal Linux, une fois le projet cloné, exécuter le script *run.sh* à la racine du projet.
```bash
# A exécuter depuis la racine du projet
bash run.sh
```
Pour fermer l'application, appuyer sur CTRL+C dans le terminal


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

En cours de réalisation
