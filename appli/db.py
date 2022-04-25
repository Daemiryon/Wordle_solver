from logging import fatal, raiseExceptions
import sqlite3
database = "data/database.db"

def addUser() -> int :
    """
    Ajoute un utilisateur dans la base de donnée en incrémentant l'ID du dernier joueur, et retourne cet ID.
    """
    try:
        connexion = sqlite3.connect(database)
        cursor = connexion.cursor()

        newId = 1
        temp = cursor.execute("SELECT max(idPlayer) FROM players").fetchone()[0]
        if temp != None:
            newId += temp
        sql_pb = "INSERT INTO PLAYERS (idPlayer) values (?)"
        cursor.executemany(sql_pb, [(newId,)])
        connexion.commit()
        print("Utilisateur enregistré avec succès")
        cursor.close()
        connexion.close()

        return newId
    except sqlite3.Error as error:
        print("Erreur lors de l'insertion dans la table USER", error)