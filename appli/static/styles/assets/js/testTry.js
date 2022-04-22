function testTry() {
    /* 
    Fonction qui vérifie si le mot essayé est de la bonne longueur et qu'il existe dans le dictionnaire.
    IN  :
    OUT : Boolean
    */
    var valid = false;
    if (guess.length == wordLength) {
        var left = 0;
        var right = validWords.length - 1;
        while (!valid && left <= right) {
            mid = Math.floor((left + right) / 2);
            if (validWords[mid] == guess) {
                valid = true;
            } else if (validWords[mid] < guess) {
                left = mid + 1
            } else {
                right = mid - 1
            }
        }
    }
    return valid;
}