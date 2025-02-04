function generateKeyboard() {

    COLOR_class = ["absent", "malplace", "bienplace"];

    const kb_color = new Map(Object.entries(kb_color_obj))

    var body = document.getElementsByClassName("Keyboard")[0];
    body.className = 'keyboard';
    var Kb = [
        ["A", "Z", "E", "R", "T", "Y", "U", "I", "O", "P"],
        ["Q", "S", "D", "F", "G", "H", "J", "K", "L", "M"],
        ["W", "X", "C", "V", "B", "N", "effacer", "enter"],
    ];

    Kb.forEach(element => {
        var ligne = document.createElement("div");
        ligne.className = "kb_line";
        element.forEach(touche => {
            var key = document.createElement("input");
            key.value = touche;
            key.type = "button";
            key.className = "key"
            if (kb_color.has(touche)) {
                key.id = COLOR_class[kb_color.get(touche)];
            } else {
                key.id = "pas_essaye";
            }
            key.dataset["touche"] = touche
            key.addEventListener('click', virt_kb_input);
            ;
            ligne.appendChild(key);
        });
        body.appendChild(ligne);
        console.log(element);
    });
}

function virt_kb_input(event) {
    input(event.target.dataset["touche"])
}



function input(key) {
    key = key.toUpperCase();

    switch (key) {
        case "BACKSPACE":
        case "EFFACER":
            retire_lettre();
            console.log(key)
            break;

        case "ENTER":
            if (testTry()) {
                post_new_try();
            } else {
                var row = document.getElementById(`tr_${cursor}`);

                row.className = "tr_shake";
                setTimeout(() => {
                    row.className = "";
                }, 2000);


            }
            console.log(testTry())
            break;

        default:
            if (/[A-Z]/.test(key)) {
                ajout_lettre(key);
                console.log(key)
            }
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
function post_new_try() {
    const form = document.createElement('form');
    form.method = 'post';
    form.action = '/currentGame';
    document.body.appendChild(form);
    const data1 = document.createElement('input');
    data1.type = 'hidden';
    data1.name = 'guess';
    data1.value = guess;
    form.appendChild(data1);
    const data2 = document.createElement('input');
    data2.type = 'hidden';
    data2.name = 'cursor';
    data2.value = cursor;
    form.appendChild(data2);
    form.submit();
}

function input_keyboard() {
    document.addEventListener("keypress", function (e) {
        console.log(e);
        input(e.key.toUpperCase());
    })
    document.addEventListener("keydown", function (e) {
        console.log(e);
        if (e.key == "Backspace") {
            input("EFFACER");
        }
    })
}