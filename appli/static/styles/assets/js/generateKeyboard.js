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
            var key = document.createElement("dive");
            var text = document.createTextNode(touche);
            key.className = "key";
            key.appendChild(text);
            ligne.appendChild(key);
        });
        body.appendChild(ligne);
        console.log(element);
    });
}