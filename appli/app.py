from contextlib import nullcontext
from crypt import methods
from flask import Flask,render_template,g,redirect,url_for,request
import sqlite3
app = Flask(__name__)

DATABASE = "./data/database.db"

@app.route('/', methods=['GET'])
def root():
    '''
    Fonction qui affiche la page lors de l'arrivée sur le site.
    Redirige sur la page d'initialisation d'une partie si le joueur n'a pas de partie en cours.
    Sinon, recharge la grille correspondante.

    IN :
    OUT: HTML page
    '''
    ### A modifier lorsque les fonctions userId() et unfinishedGame() seront implémentées
    runningGame = False
    # if unfinishedGame(userId()):
    if runningGame:
        return redirect("/currentGame")
    else:
        return redirect("/newGame")

@app.route('/newGame', methods=['GET'])
def parametersPage():
    '''
    Fonction qui charge la page d'initialisation d'une partie.

    IN :
    OUT: HTML page
    '''
    maxTryPossibilities = [3,4,5,6,7,8,9,10]
    wordLengthPossibilities = [5,6,7,8,9,10,11,12,13,14,15]

    nbParties,nbMoyenEssais=getStats() ##A modifier lorsqu'on reconnaîtra l'utilisateur

    return render_template(
        "parameters.html",
        MAXTRYPOSSIBILITIES=maxTryPossibilities,
        WORDLENGTHPOSSIBILITIES=wordLengthPossibilities,
        NBPARTIES=nbParties,
        NBMOYENESSAIS=nbMoyenEssais
    )

@app.route('/currentGame', methods=['GET','POST'])
def currentGame():
    '''
    Fonction qui affiche la page de la partie en cours.

    IN :
    OUT: HTML page
    '''
    ### A modifier lorsque les fonctions userId() et unfinishedGame() seront implémentées
    runningGame = False
    nbParties,nbMoyenEssais=getStats() ##A modifier lorsqu'on reconnaîtra l'utilisateur
    # if unfinishedGame(userId()):
    if runningGame:
        ### A compléter
        None
    else:
        maxTry = request.form.get("maxtry")
        wordLength = request.form.get("wordlength")
    return render_template("game.html",MAXTRY=maxTry,WORDLENGTH=wordLength,NBPARTIES=nbParties,NBMOYENESSAIS=nbMoyenEssais)

##Partie Popup stats

def getStats(myId=1) :
    ##Fonction qui récupère les stats d'un utilisateur (nombre de parties, nombre moyen d'essais max).
    ##In : idPlayer
    ##Out : nombre de parties & nombre moyen d'essais max
    con = sqlite3.connect(DATABASE)
    cur = con.cursor()
    cur.execute('SELECT COUNT(*) FROM games WHERE gameEnded == 1 AND idPlayer= ?',(myId,))
    c = cur.fetchall()
    nbParties = [e[0] for e in c]
    cur.execute('SELECT AVG(nbMaxTries) FROM games WHERE idPlayer= ?',(myId,))
    c = cur.fetchall()
    nbMaxTries_avrg = [e[0] for e in c]
    return nbParties,nbMaxTries_avrg
