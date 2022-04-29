from logging import fatal, raiseExceptions
import sqlite3
import fn
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
    
# Fonctions auxiliaires de la route '/newGame'
def isFinishedGame(idPlayer):
    with sqlite3.connect(database) as con:
        cur = con.cursor()
        idLastGame = cur.execute("SELECT idLastGame FROM PLAYERS WHERE idPlayer=?",(idPlayer,)).fetchone()[0]
        if idLastGame == 0:
            return 1
        gameEnded = cur.execute("SELECT gameEnded FROM GAMES WHERE idPlayer=? AND idGame=?",(idPlayer,idLastGame)).fetchone()[0]
        return gameEnded

# -----
# Fonctions auxiliaires pour la fin de partie
def endGame(idPlayer,idGame) :
    '''
    Fonction qui MAJ la BD (gameEnded =1)
    
    IN : idPlayer, idGame
    OUT : -
    '''
    con = sqlite3.connect(database)
    cur = con.cursor()

    cur.execute('UPDATE games SET gameEnded=1 WHERE idPlayer=? AND idGame=?',(idPlayer,idGame))
    cur.close()
    con.commit()



# -----
# Fonctions auxiliaires pour les stastiques et les paramètres
def getStats(myId=1) : 
    '''
    Fonction qui récupère les stats d'un utilisateur (nombre de parties, plus gros score).

    IN  : idPlayer (int)
    OUT : nbParties (int), highestScore (int)
    '''
    con = sqlite3.connect(database)
    cur = con.cursor()
    cur.execute('SELECT COUNT(*) FROM games WHERE gameEnded == 1 AND idPlayer= ?',(myId,))
    c = cur.fetchall()
    nbParties = c[0][0]

    #Partie HighestScore

    cur.execute('SELECT MAX(idTry) FROM tries JOIN games ON tries.idGame=games.idGame WHERE games.idPlayer= ? and games.gameEnded=1 group by tries.idGame',(myId,))
    c = cur.fetchall()
    temp= [e[0] for e in c]
    if temp == [] :
        highestScore = 0
    else :
        minIdTry = min(temp)
        
        cur.execute('SELECT MAX(idTry),tries.idGame from tries JOIN games ON tries.idGame=games.idGame WHERE games.idPlayer= ? and games.gameEnded=1 group by tries.idGame',(myId,))
        c = cur.fetchall()
        temp= [e for e in c]
        temp_idGame = []
        for ele in temp :
            if ele[0] == minIdTry :
                temp_idGame.append(ele[1])
        
        Scores = []
        for i in range(len(temp_idGame)) :
            wordToFind = cur.execute('SELECT wordToFind FROM games WHERE games.idPlayer= ? and games.gameEnded=1 and games.idGame =?',(myId,temp_idGame[i])).fetchone()[0]
            lastTry = cur.execute('SELECT MAX(idTry) from tries JOIN games ON tries.idGame=games.idGame WHERE games.idPlayer =? and games.gameEnded=1 and games.idGame=?',(myId,temp_idGame[i])).fetchone()[0]
            wordLastTry = cur.execute('SELECT wordTried FROM tries JOIN games ON tries.idGame=games.idGame WHERE games.idPLayer = ? and games.gameEnded =1 and games.idGame =? and idTry =?',(myId,temp_idGame[i],lastTry)).fetchone()[0]
            
            score_user = int(round(len(wordToFind)/minIdTry,3)*1000)*(wordLastTry==wordToFind)
            Scores.append( score_user )
        
        highestScore = max(Scores)

    return nbParties,highestScore

def getNbTries(idPlayer,idGame) :
    con = sqlite3.connect(database)
    cur = con.cursor()
    nbTries = cur.execute('SELECT MAX(idTry) from tries where tries.idPlayer=? and tries.idGame=?',(idPlayer,idGame)).fetchone()[0]
    return nbTries 
# -----
# Fonctions auxliaires de la route '/currentGame'
def get_game_data(idPlayer=1) :
    '''
    Fonction qui récupère les données de la partie en cours pour le joueur
    
    IN  : idPlayer (int)
    OUT : wordLength (str), maxTry (str), tries (List[str]), colors (List[List[int]]),idGame (int)
    '''
    con = sqlite3.connect(database)
    cur = con.cursor()
    idGame = cur.execute("SELECT idLastGame FROM PLAYERS WHERE idPlayer=?",(idPlayer,)).fetchone()[0]
    maxTry = cur.execute("SELECT nbMaxTries FROM GAMES WHERE idPlayer=? AND idGame=?",(idPlayer,idGame)).fetchone()[0]
    wordToFind = cur.execute("SELECT wordToFind FROM GAMES WHERE idPlayer=? AND idGame=?",(idPlayer,idGame)).fetchone()[0]
    wordLength = len(wordToFind)
    triesData = cur.execute("select wordTried from tries where idplayer = ? and idgame = ?",(idPlayer,idGame)).fetchall()
    tries = [e[0] for e in triesData]
    colors = [fn.couleur(guess,wordToFind) for guess in tries]
    return wordToFind,wordLength,maxTry,tries,colors,idGame


#----
def createNewGame(session_id, maxTry, wordToFind,difficulty):
    with sqlite3.connect(database) as con:
                cur = con.cursor()
                temp = cur.execute("SELECT MAX(idGame) FROM GAMES WHERE idPlayer=?",(session_id,)).fetchone()[0]
                idGame = 1
                if temp != None:
                    idGame += temp
                cur.execute("INSERT INTO GAMES VALUES (?,?,?,0,?,0,?)",(session_id,idGame,maxTry,wordToFind,difficulty))
                cur.execute("UPDATE PLAYERS SET idLastGame=?",(idGame,))
                cur.close()
                con.commit()

def insertNewTry(session_id, guess, idGame):
    with sqlite3.connect(database) as con:
            cur = con.cursor()
            temp = cur.execute("SELECT MAX(idTry) FROM TRIES WHERE idPlayer=? AND idGame=?",(session_id,idGame)).fetchone()[0]
            idTry = 1
            if temp != None:
                idTry += temp
            cur.execute("INSERT INTO TRIES VALUES (?,?,?,?)",(session_id,idGame,idTry,guess))
            cur.close()
            con.commit()
