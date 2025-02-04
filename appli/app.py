from crypt import methods
from flask import Flask,render_template,g,redirect,url_for,request,session
import db
import fn
app = Flask(__name__)
app.secret_key = "any random string" #chiffrement des cookies sessions

#Rend le cookie de la session persistant
@app.before_request
def make_session_permanent():
    session.permanent = True 

@app.route('/', methods=['GET'])
def root():
    '''
    Fonction qui affiche la page lors de l'arrivée sur le site.
    Redirige sur la page d'initialisation d'une partie si le joueur n'a pas de partie en cours.
    Sinon, recharge la grille correspondante.

    IN :
    OUT: HTML page
    '''
    print('----------------------------------------------')
    if "id" not in session or db.cookieUnsyncedDb(session['id']):
        print("Utilisateur non reconnu. Ajout à la base de données")
        session["id"] = db.addUser()
    else:
        print("Utilisateur %s reconnu." % session["id"])
    print(session['id'])

    if not db.isFinishedGame(session["id"]):
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
    nbParties,highestScore = db.getStats(session["id"]) 
    if request.method == "POST":
        try:
            maxTry = request.form.get("maxtry")
            wordLength = int(request.form.get("wordlength"))
            wordLength= min(max(5,wordLength),15)
            difficulty = int(request.form.get("Difficulty"))
            difficulty = min(max(0,difficulty),9)
            wordToFind = fn.get_a_word(str(wordLength),int(difficulty))

        except:
            maxTry = 6
            wordLength = 6
            difficulty = 0
            wordToFind = 'NOODLE'

        db.createNewGame(session['id'], maxTry, wordToFind,int(difficulty))
        return redirect('/currentGame')    

    else:
        maxTryPossibilities = [3,4,5,6,7,8,9,10]
        wordLengthPossibilities = [5,6,7,8,9,10,11,12,13,14,15]
        return render_template("parameters.html",
            MAXTRYPOSSIBILITIES=maxTryPossibilities,
            WORDLENGTHPOSSIBILITIES=wordLengthPossibilities,
            
            NBPARTIES=nbParties,
            HIGHESTSCORE = highestScore
        )

@app.route('/currentGame', methods=['GET','POST'])
def currentGame():
    '''
    Fonction qui affiche la page de la partie en cours.

    IN :
    OUT: HTML page
    '''  
    nbParties,highestScore = db.getStats(session["id"]) 
    
    wordToFind,wordLength,maxTry,tries,colors,idGame = db.get_game_data(session["id"]) 
    cursor = len(tries)

    kb_color = {}
    for guess,color in zip(tries,colors): 
        kb_color = fn.maj_keyboard_color(kb_color,guess,color)

    if request.method == 'POST': #l'utilisateur a entré un mot valide
        guess = request.form.get("guess")
        db.insertNewTry(session['id'], guess, idGame)
        cursor += 1
        colors.append(fn.couleur(guess,wordToFind))
        tries.append(guess)
        kb_color = fn.maj_keyboard_color(kb_color,guess,colors[-1])
        if fn.testEndGame(wordToFind,guess,cursor,maxTry):
            db.endGame(session["id"],idGame)
            nbTries = db.getNbTries(session["id"],idGame)
            score = db.calcul_score(wordLength,nbTries,wordToFind,guess,session["id"],idGame)
            db.update_score(session["id"],idGame,score)
            nbParties,highestScore = db.getStats(session["id"])
            return render_template("game.html",
                TESTENDGAME = True,
                WHICHEND = fn.whichEnd(wordToFind,guess),
                KBCOLOR=kb_color,
                MAXTRY=maxTry,
                WORDLENGTH=wordLength,
                CURSOR = cursor,
                MOTSVALIDES = fn.get_valid_words(wordLength),
                TRIES = tries + [' '*wordLength]*(maxTry-cursor),
                COLOR = colors + [[0,]*wordLength]*(maxTry-cursor),
              
                NBPARTIES=nbParties,
                MOTATROUVER=wordToFind,
                NBESSAIS=nbTries,

                SCORE=score,
                HIGHESTSCORE = highestScore
            )
        return redirect(url_for('currentGame'))

    return render_template("game.html",
        KBCOLOR=kb_color,
        MAXTRY=maxTry,
        WORDLENGTH=wordLength,
        CURSOR = cursor,
        MOTSVALIDES = fn.get_valid_words(wordLength),
        TRIES = tries + [' '*wordLength]*(maxTry-cursor),
        COLOR = colors + [[0,]*wordLength]*(maxTry-cursor),
        
        NBPARTIES=nbParties,
        HIGHESTSCORE = highestScore
    )

@app.route('/restart')
def restart():
    return redirect('/')

@app.route('/quitGame')
def quitGame():
    idGame = db.getIdGameLeft(session["id"])
    db.removeCurrentGame(session['id'],idGame)
    return redirect('/newGame')