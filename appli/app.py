from contextlib import nullcontext
from crypt import methods
from flask import Flask,render_template,g,redirect,url_for,request,session
import sqlite3
import db
import json
from random import choice
app = Flask(__name__)
app.secret_key = "any random string" #chiffrement des cookies sessions
DATABASE = "./data/database.db"


@app.before_request
def make_session_permanent():
    session.permanent = True #Rend le cookie de la session persistant

def maj_keyboard_color(kb_color,guess,colors):
    for letter,color in zip(guess,colors):
        if letter in kb_color:
            kb_color[letter]=max(kb_color[letter],color)
        else : 
            kb_color[letter]=color
    
    return kb_color


# -----
# Fonctions auxiliaires de la route '/newGame'
def get_a_word(WORDLENGTH):
    '''
    Fonction qui retourne un mot de taille WORDLENGTH du dictionnaire 
    
    IN : WORDLENGTH ( int )
    OUT : word ( str )
    '''
    return choice(get_valid_words(WORDLENGTH))


# -----
# Fonctions auxliaires de la route '/currentGame'
def get_game_data(idPlayer=1) :
    '''
    Fonction qui récupère les données de la partie en cours pour le joueur
    
    IN  : idPlayer (int)
    OUT : wordLength (str), maxTry (str), tries (List[str]), colors (List[List[int]]),idGame (int)
    '''
    con = sqlite3.connect(DATABASE)
    cur = con.cursor()
    idGame = cur.execute("SELECT idLastGame FROM PLAYERS WHERE idPlayer=?",(idPlayer,)).fetchone()[0]
    maxTry = cur.execute("SELECT nbMaxTries FROM GAMES WHERE idPlayer=? AND idGame=?",(idPlayer,idGame)).fetchone()[0]
    wordToFind = cur.execute("SELECT wordToFind FROM GAMES WHERE idPlayer=? AND idGame=?",(idPlayer,idGame)).fetchone()[0]
    wordLength = len(wordToFind)
    triesData = cur.execute("select wordTried from tries where idplayer = ? and idgame = ?",(idPlayer,idGame)).fetchall()
    tries = [e[0] for e in triesData]
    colors = [couleur(guess,wordToFind) for guess in tries]
    return wordToFind,wordLength,maxTry,tries,colors,idGame

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

def testEndGame(wordToFind,guess,cursor,maxTry):
    if guess == wordToFind or cursor >= maxTry:
        return True
    return False


# -----
# Fonctions auxiliaires pour les stastiques et les paramètres
def getStats(myId=1) : ##On peut ajouter le winrate si on a le temps (wordTried == wordToFind && max(idTry)<=nbMaxTries) (?)
    '''
    Fonction qui récupère les stats d'un utilisateur (nombre de parties, nombre moyen d'essais).

    IN  : idPlayer (int)
    OUT : nbParties (int), nbTryMax_avrg (float)
    '''
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

# -----
# Fonctions auxiliaires pour la fin de partie
def endGame(idPlayer,idGame) :
    '''
    Fonction qui MAJ la BD (gameEnded =1)
    
    IN : idPlayer, idGame
    OUT : -
    '''
    con = sqlite3.connect(DATABASE)
    cur = con.cursor()

    cur.execute('UPDATE games SET gameEnded=1 WHERE idPlayer=? AND idGame=?',(idPlayer,idGame))
    cur.close()
    con.commit()


def whichEnd(wordToFind,guess) :
    '''
    Fonction qui détermine si l'utilisateur a gagné ou perdu la partie
    '''
    if guess == wordToFind :
        return True #Winning case
    return False #Losing case


# -----
# Routes
@app.route('/', methods=['GET'])
def root():
    '''
    Fonction qui affiche la page lors de l'arrivée sur le site.
    Redirige sur la page d'initialisation d'une partie si le joueur n'a pas de partie en cours.
    Sinon, recharge la grille correspondante.

    IN :
    OUT: HTML page
    '''
    if "id" not in session:
        session["id"] = db.addUser()
    else:
        print("Utilisateurs numero %s est reconnu." % session["id"])

    ### A modifier lorsque les fonctions userId() et unfinishedGame() seront implémentées
    runningGame = 0
    # if unfinishedGame(session["id"]):
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
    nbParties,nbMoyenEssais = getStats(session["id"]) 

    if request.method == "POST":
        maxTry = request.form.get("maxtry")
        wordLength = request.form.get("wordlength")

        if wordLength == None or maxTry == None:
            error = 1
            maxTryPossibilities = [3,4,5,6,7,8,9,10]
            wordLengthPossibilities = [5,6,7,8,9,10,11,12,13,14,15]
            return render_template("parameters.html",
                MAXTRYPOSSIBILITIES = maxTryPossibilities,
                WORDLENGTHPOSSIBILITIES = wordLengthPossibilities,
                NBPARTIES = nbParties,
                NBMOYENESSAIS = nbMoyenEssais,
                ERROR = error
            )
        
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
        error = 0
        maxTryPossibilities = [3,4,5,6,7,8,9,10]
        wordLengthPossibilities = [5,6,7,8,9,10,11,12,13,14,15]
        return render_template("parameters.html",
            MAXTRYPOSSIBILITIES=maxTryPossibilities,
            WORDLENGTHPOSSIBILITIES=wordLengthPossibilities,
            NBPARTIES=nbParties,
            NBMOYENESSAIS=nbMoyenEssais,
            ERROR = error
        )

@app.route('/currentGame', methods=['GET','POST'])
def currentGame():
    '''
    Fonction qui affiche la page de la partie en cours.

    IN :
    OUT: HTML page
    '''
    nbParties,nbMoyenEssais = getStats(session["id"]) 
    
    wordToFind,wordLength,maxTry,tries,colors,idGame = get_game_data(session["id"]) 
    cursor = len(tries)

    kb_color = {}
    for guess,color in zip(tries,colors): 
        kb_color = maj_keyboard_color(kb_color,guess,color)

    if request.method == 'POST':
        guess = request.form.get("guess")
        cursor_page = int(request.form.get("cursor"))
        print(cursor,cursor_page)
        if cursor_page==cursor:
            print('ok')
            with sqlite3.connect(DATABASE) as con:
                cur = con.cursor()
                temp = cur.execute("SELECT MAX(idTry) FROM TRIES WHERE idPlayer=? AND idGame=?",(session["id"],idGame)).fetchone()[0]
                idTry = 1
                if temp != None:
                    idTry += temp
                cur.execute("INSERT INTO TRIES VALUES (?,?,?,?)",(session["id"],idGame,idTry,guess))
                cur.close()
                con.commit()

            cursor += 1
            colors.append(couleur(guess,wordToFind))
            tries.append(guess)
            kb_color = maj_keyboard_color(kb_color,guess,colors[-1])


            if testEndGame(wordToFind,guess,cursor,maxTry):
                endGame(session["id"],idGame)
                nbParties,nbMoyenEssais = getStats(session["id"])
                return render_template("game.html",
                    TESTENDGAME = True,
                    WHICHEND = whichEnd(wordToFind,guess),
                    KBCOLOR=kb_color,
                    MAXTRY=maxTry,
                    WORDLENGTH=wordLength,
                    CURSOR = cursor,
                    MOTSVALIDES = get_valid_words(wordLength),
                    TRIES = tries + [' '*wordLength]*(maxTry-cursor),
                    COLOR = colors + [[0,]*wordLength]*(maxTry-cursor),
                    NBPARTIES=nbParties,
                    NBMOYENESSAIS=nbMoyenEssais,
                    MOTATROUVER=wordToFind
                )

    return render_template("game.html",
        KBCOLOR=kb_color,
        MAXTRY=maxTry,
        WORDLENGTH=wordLength,
        CURSOR = cursor,
        MOTSVALIDES = get_valid_words(wordLength),
        TRIES = tries + [' '*wordLength]*(maxTry-cursor),
        COLOR = colors + [[0,]*wordLength]*(maxTry-cursor),
        NBPARTIES=nbParties,
        NBMOYENESSAIS=nbMoyenEssais,
        )