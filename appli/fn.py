import json
from random import choice

def maj_keyboard_color(kb_color,guess,colors):
    for letter,color in zip(guess,colors):
        if letter in kb_color:
            kb_color[letter]=max(kb_color[letter],color)
        else : 
            kb_color[letter]=color
    
    return kb_color


def get_a_word(WORDLENGTH,difficulte=0):
    '''
    Fonction qui retourne un mot de taille WORDLENGTH du dictionnaire 
    
    IN : WORDLENGTH ( int ), difficulte ( int ) in {0,1,2}
    OUT : word ( str )
    '''
    Liste_mots = json.load(open('./data/dictionnaires/liste_mots_a_trouver.json','r'))[int(WORDLENGTH)]
    print(Liste_mots[difficulte*len(Liste_mots)//4:(difficulte+1)*len(Liste_mots)//4])
    return choice(Liste_mots[difficulte*len(Liste_mots)//4:(difficulte+1)*len(Liste_mots)//4])


# -----
# Fonctions auxliaires de la route '/currentGame'

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
# Fonctions auxiliaires pour la fin de partie
def whichEnd(wordToFind,guess) :
    '''
    Fonction qui détermine si l'utilisateur a gagné ou perdu la partie
    '''
    if guess == wordToFind :
        return True #Winning case
    return False #Losing case