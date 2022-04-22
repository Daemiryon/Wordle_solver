#!/bin/bash
if [ -e .env ]
then
source .env/bin/activate
else
python3 -m venv .env
source .env/bin/activate
pip install -r requirements.txt
fi
cd appli
export FLASK_APP="app.py"
flask run