var btnPopupStats = document.getElementById('btnPopupStats');
var overlayStats = document.getElementById("overlayStats");
var btnCloseStats = document.getElementById("btnCloseStats");

btnPopupStats.addEventListener('click',openPopupStats);

function openPopupStats(){
    overlay.style.display = "block";
    popupStats.style.display = "block";
}

btnCloseStats.addEventListener('click',closePopupStats);

function closePopupStats(){
    overlay.style.display = "none";
    popupStats.style.display = "none";
}

btnPopupRegles.addEventListener('click',openPopupRegles);

function openPopupRegles(){
    overlay.style.display = "block";
    popupRegles.style.display = "block";
}

btnCloseRegles.addEventListener('click',closePopupRegles);

function closePopupRegles(){
    overlay.style.display = "none";
    popupRegles.style.display = "none";
}