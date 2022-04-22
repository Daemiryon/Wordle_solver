function generateKeyboard() {

    var body = document.getElementsByClassName("Keyboard")[0];
    body.className = 'keyboard';
    var Kb = [
        ["A", "Z", "E", "R", "T", "Y", "U", "I", "O", "P"],
        ["Q", "S", "D", "F", "G", "H", "J", "K", "L", "M"],
        ["W", "X", "C", "V", "B", "N", "effacer", "entree"],
    ];

    Kb.forEach(element => {
        var ligne = document.createElement("div");
        ligne.className = "kb_line";
        element.forEach(touche => {
            var key = document.createElement("button");
            var text = document.createTextNode(touche);
            key.className = "key";
            key.dataset["touche"] = touche
            key.appendChild(text);
            key.addEventListener('click', input)
            ligne.appendChild(key);
        });
        body.appendChild(ligne);
        console.log(element);
    });
}

function input(event) {
    key = event.target.dataset["touche"]


    switch (key) {
        case "effacer":
            retire_lettre();
            console.log(key)
            break;

        case "entree":
            // if (testTry()) {
            //     //     post_new_try();
            //     //      { mot_propose, cursor, lite des tries }
            // }
            console.log(testTry())
            break;

        default:
            ajout_lettre(key);
            console.log(key)
            break;
    }


}

function ajout_lettre(lettre) {
    if (guess.length < wordLength) {
        var cell = document.getElementById(cursor * wordLength + guess.length);
        cell.textContent = lettre;
        guess = guess + lettre;
        console.log(guess);
    }

}

function retire_lettre() {
    if (guess.length > 0) {
        guess = guess.substring(0, guess.length - 1);
        var cell = document.getElementById(cursor * wordLength + guess.length);
        cell.textContent = "";

        console.log(guess);
    }

}
