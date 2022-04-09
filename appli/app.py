from operator import methodcaller
from flask import Flask,render_template,g,redirect,url_for,request
app = Flask(__name__)

@app.route('/')
def retourPageWordle():
    return(redirect('/PageWordle'))

@app.route('/PageWordle',methods=["GET","POST"])
def pageWordle():
        return render_template("PageWordle.html")


