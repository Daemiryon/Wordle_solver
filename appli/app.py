from contextlib import nullcontext
from crypt import methods
from flask import Flask,render_template,g,redirect,url_for,request,session
import sqlite3
import db
app = Flask(__name__)
app.secret_key = "any random string" #chiffrement des cookies sessions
DATABASE = "./data/database.db"

@app.before_request
def make_session_permanent():
    session.permanent = True #Rend le cookie de la session persistant


@app.route('/', methods=['GET'])
def root():
    '''
    Fonction qui affiche la page lors de l'arrivée sur le site.
    Redirige sur la page d'initialisation d'une partie si le joueur n'a pas de partie en cours.
    Sinon, recharge la grille correspondante.

    IN :
    OUT: HTML page
    '''
    
    ### Login
    if "id" not in session:
        session["id"] = db.addUser()
    else:
        print("Utilisateurs numero %s est déjà authentifié." % session["id"])


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
    return render_template(
        "parameters.html",
        MAXTRYPOSSIBILITIES=maxTryPossibilities,
        WORDLENGTHPOSSIBILITIES=wordLengthPossibilities
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
    # if unfinishedGame(userId()):
    if runningGame:
        ### A compléter
        None
    else:
        maxTry = request.form.get("maxtry")
        wordLength = request.form.get("wordlength")
    return render_template("game.html",MAXTRY=maxTry,WORDLENGTH=wordLength)
