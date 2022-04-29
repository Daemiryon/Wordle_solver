
var overlayEnd = document.getElementById("overlayEnd");
var btnCloseEnd = document.getElementById("btnCloseEnd");

btnCloseEnd.addEventListener('click',closePopupEnd);

function closePopupEnd(){
    overlayEnd.style.display = "none";
    popupEnd.style.display = "none";
}

