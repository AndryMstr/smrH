import requests
from flask import Flask
import pandas as pd
app = Flask(__name__)


@app.route("/")
def hello():
    return "стартовая страница"


@app.route("/data")  # запрос для датчика температуры
def push_new_temp():
    t_bedroom = requests.get('http://192.168.1.207/temp')
    h_bedroom = requests.get('http://192.168.1.207/humidity')
    t_balcony = requests.get('http://192.168.1.109/temp')
    h_balcony = requests.get('http://192.168.1.109/humidity')
    df = pd.DataFrame([[t_bedroom.text, h_bedroom.text],
                       [t_balcony.text, h_balcony.text]],
                      index=['bedroom', 'balcony'],
                      columns=['temp', 'humidity'])
    return df.to_html()


if __name__ == "__main__":
    app.run(host='192.168.1.88')
