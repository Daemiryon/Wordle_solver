function generateGrid(maxTry,wordLength) {
    
    var body = document.getElementsByClassName("grid")[0];

    var tb = document.createElement("table");
    var tb_body = document.createElement("tbody");

    for (let i=0;i<maxTry;i++){
        var row = document.createElement("tr");
        for (let j=0;j<wordLength;j++){
            var cell = document.createElement("td");
            var node = document.createTextNode("");
            cell.id = i*wordLength+j
            cell.appendChild(node);
            row.appendChild(cell);
        }
        tb_body.appendChild(row);
    }
    tb.appendChild(tb_body);
    body.appendChild(tb);
}