from contextlib import nullcontext
from crypt import methods
from flask import Flask,render_template,g,redirect,url_for,request,session
import sqlite3
import db
import json
from random import choice
app = Flask(__name__)
app.secret_key = "any random string" #chiffrement des cookies sessions
DATABASE = "data/database.db"


@app.before_request
def make_session_permanent():
    session.permanent = True #Rend le cookie de la session persistant

def get_valid_words(WORDLENGTH):
    '''
    Fonction qui retourne une liste de mots de taille WORDLENGTH du dictionnaire 
    
    IN : WORDLENGTH ( int )
    OUT : word ( List [ str ] )
    '''
    dic_file = open(f"./data/dictionnaires/{WORDLENGTH}_lettres.json")
    Mots_valides=json.load(dic_file)
    dic_file.close()
    return Mots_valides

def get_a_word(WORDLENGTH):
    '''
    Fonction qui retourne un mot de taille WORDLENGTH du dictionnaire 
    
    IN : WORDLENGTH ( int )
    OUT : word ( str )
    '''
    return choice(get_valid_words(WORDLENGTH))

def couleur(guess,target):
    Couleurs=[0,]*len(target)
    reste ={}
    
    for i in range(len(target)):
        if guess[i]==target[i]:
            Couleurs[i]=2
        else:
            if target[i] not in reste:
                reste[target[i]]=1
            else :
                reste[target[i]]+=1
        
    
    for i in range(len(target)):
        if  guess[i] in reste and reste[guess[i]]!=0 :
            reste[guess[i]]-=1
            Couleurs[i]=max(1,Couleurs[i])


    return Couleurs
        
# -----

@app.route('/', methods=['GET'])
def root():
    '''
    Fonction qui affiche la page lors de l'arrivée sur le site.
    Redirige sur la page d'initialisation d'une partie si le joueur n'a pas de partie en cours.
    Sinon, recharge la grille correspondante.

    IN :
    OUT: HTML page
    '''
    ### getUser()
    ### Login - ne s'execute pour l'instant que sur la route '/', a corriger dans le futur
    if "id" not in session:
        session["id"] = db.addUser()
    else:
        print("Utilisateurs numero %s est reconnu." % session["id"])

    ### A modifier lorsque les fonctions userId() et unfinishedGame() seront implémentées
    runningGame = False
    # if unfinishedGame(userId()):
    if runningGame:
        return redirect("/currentGame")
    else:
        return redirect("/newGame")

@app.route('/newGame', methods=['GET','POST'])
def parametersPage():
    '''
    Fonction qui charge la page d'initialisation d'une partie.

    IN :
    OUT: HTML page
    '''
    nbParties,nbMoyenEssais = getStats(session["id"]) ##A modifier lorsqu'on reconnaîtra l'utilisateur
    motATrouver,nbEssais = getResults() ##idem

    if request.method == "POST":
        maxTry = request.form.get("maxtry")
        wordLength = request.form.get("wordlength")
        wordToFind = get_a_word(wordLength)
        with sqlite3.connect(DATABASE) as con:
            cur = con.cursor()
            temp = cur.execute("SELECT MAX(idGame) FROM GAMES WHERE idPlayer=?",(session["id"],)).fetchone()[0]
            idGame = 1
            if temp != None:
                idGame += temp
            cur.execute("INSERT INTO GAMES VALUES (?,?,?,0,?)",(session["id"],idGame,maxTry,wordToFind))
            cur.execute("UPDATE PLAYERS SET idLastGame=?",(idGame,))
            cur.close()
            con.commit()
        return redirect('/currentGame')

    else:
        maxTryPossibilities = [3,4,5,6,7,8,9,10]
        wordLengthPossibilities = [5,6,7,8,9,10,11,12,13,14,15]
        return render_template("parameters.html",
            MAXTRYPOSSIBILITIES=maxTryPossibilities,
            WORDLENGTHPOSSIBILITIES=wordLengthPossibilities,
            NBPARTIES=nbParties,
            NBMOYENESSAIS=nbMoyenEssais,
            MOTATROUVER=motATrouver,
            NBESSAIS=nbEssais
        )

@app.route('/currentGame', methods=['GET','POST'])
def currentGame():
    '''
    Fonction qui affiche la page de la partie en cours.

    IN :
    OUT: HTML page
    '''
    nbParties,nbMoyenEssais=getStats() ##A modifier lorsqu'on reconnaîtra l'utilisateur
    motATrouver,nbEssais=getResults() ##idem
    with sqlite3.connect(DATABASE) as con:
        cur = con.cursor()
        idGame = cur.execute("SELECT idLastGame FROM PLAYERS WHERE idPlayer=?",(session["id"],)).fetchone()[0]
        maxTry = cur.execute("SELECT nbMaxTries FROM GAMES WHERE idPlayer=? AND idGame=?",(session["id"],idGame)).fetchone()[0]
        wordToFind = cur.execute("SELECT wordToFind FROM GAMES WHERE idPlayer=? AND idGame=?",(session["id"],idGame)).fetchone()[0]
        wordLength = len(wordToFind)
    
    return render_template("game.html",
        MAXTRY=maxTry,
        WORDLENGTH=wordLength,
        NBPARTIES=nbParties,
        NBMOYENESSAIS=nbMoyenEssais,
        MOTATROUVER=motATrouver,
        NBESSAIS=nbEssais)






##Partie stats

def getStats(myId=1) : ##On peut ajouter le winrate si on a le temps (wordTried == wordToFind && max(idTry)<=nbMaxTries) (?)
    ##Fonction qui récupère les stats d'un utilisateur (nombre de parties, nombre moyen d'essais).
    ##In : idPlayer
    ##Out : nombre de parties & nombre moyen d'essais
    con = sqlite3.connect(DATABASE)
    cur = con.cursor()
    cur.execute('SELECT COUNT(*) FROM games WHERE gameEnded == 1 AND idPlayer= ?',(myId,))
    c = cur.fetchall()
    nbParties = c[0][0]
    cur.execute('SELECT MAX(idTry) FROM tries JOIN games ON tries.idGame=games.idGame WHERE tries.idPlayer= ? and games.gameEnded=1 group by tries.idGame',(myId,))
    c = cur.fetchall()
    nbTryMax = [e[0] for e in c]
    nbTryMax_avrg = 0
    if nbParties != 0 :
        for i in range(len(nbTryMax)) :
            nbTryMax_avrg += nbTryMax[i]
        nbTryMax_avrg = nbTryMax_avrg/nbParties
    return nbParties,nbTryMax_avrg

def getResults(myId=1,myGame=2) :
    ##Fonction qui récupère les résultats d'une partie d'un utilisateur (mot à trouver, nombre d'essais).
    ##In : idPlayer, idGame
    ##Out : mot à trouver & nombre d'essais
    con = sqlite3.connect(DATABASE)
    cur = con.cursor()
    cur.execute('SELECT wordToFind FROM games WHERE idGame= ? AND idPlayer= ?',(myGame,myId))
    c = cur.fetchall()
    motATrouver = c[0][0]
    cur.execute('SELECT MAX(idTry) FROM tries JOIN games ON tries.idGame=games.idGame WHERE tries.idPlayer= ? and tries.idGame = ?',(myId,myGame))
    c = cur.fetchall()
    nbTryMax = c[0][0]
    return motATrouver,nbTryMax
