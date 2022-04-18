var btnPopupStats = document.getElementById('btnPopupStats');
var overlayStats = document.getElementById("overlayStats");
var btnCloseStats = document.getElementById("btnCloseStats");

btnPopupStats.addEventListener('click',openPopupStats);

function openPopupStats(){
    overlayStats.style.display = "block";
}

btnCloseStats.addEventListener('click',closePopupStats);

function closePopupStats(){
    overlayStats.style.display = "none";
}