from flask import Flask, request
import shelve
import pandas as pd
app = Flask(__name__)


@app.route("/")
def hello():
    return "Здесь будет красивая заставка и кнопки умного дома, Которые сделает Андрей Андреевич"


@app.route("/push_new_temp")  # запрос для датчика температуры
def push_new_temp():
    new_temp = request.args.get('new_temp', default=0, type=int)
    # помещаем в переменную new_temp аргумент из GET запроса
    with shelve.open('data.shl') as shl:
        shl['temp'] = new_temp
    return 'i get new temp'


@app.route("/push_light")
def push_light():
    new_light_value = request.args.get('new_light', default=0, type=int)
    with shelve.open('data.shl') as shl:
        shl['light'] = new_light_value
    return 'i get new humidity'


@app.route("/push_new_humidity")  # запрос для датчика влажности
def push_new_humidity():
    new_humidity = request.args.get('new_humidity', default=0, type=int)
    # помещаем в переменную new_temp аргумент из GET запроса
    with shelve.open('data.shl') as shl:
        shl['humidity'] = new_humidity
    return 'i get new humidity'


@app.route("/push_new_movement")  # запрос для датчика движения
def push_new_movement():
    new_movement = request.args.get('new_movement', default=0, type=int)
    # помещаем в переменную new_temp аргумент из GET запроса
    with shelve.open('data.shl') as shl:
        shl['movement'] = new_movement
    return 'i get new_movement'


@app.route("/get_actual_data")  # запрос на получения актуальных данных
def get_actual_data():
    with shelve.open('data.shl') as shl:
        data = {}
        data['light'] = shl['light']
        # data['humidity'] = shl['humidity']
        # data['movement'] = shl['movement']
    return pd.DataFrame({"value": data}).to_html()


if __name__ == "__main__":
    app.run(host='192.168.1.88')
