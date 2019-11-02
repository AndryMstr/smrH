import datetime
import json
import sqlite3
from typing import List

import requests
from flask import Flask
from apscheduler.schedulers.background import BackgroundScheduler
import pandas as pd
app = Flask(__name__)

URLS = ['http://172.20.10.6', 'http://172.20.10.5']
DB_NAME = 'smrh.db'


def one_esp_data(url: str):
    base_info = json.loads(requests.get(url).text)
    poss_datas = [data_name for data_name in base_info['data'].split(';') if data_name != '']
    res = {}
    for data_name in poss_datas:
        res[data_name] = float(requests.get(f"{url}/{data_name}").text)
    res['time'] = datetime.datetime.now()
    res['sensor_name'] = base_info['sensor_name']
    return res


def all_esp_data(urls: List[str], db_name, if_exists: str = 'append'):
    all_res = []
    for url in urls:
        all_res.append(one_esp_data(url=url))
    if len(all_res) > 0:
        un_data = pd.DataFrame(all_res)
        with sqlite3.connect(db_name) as conn:
            un_data.to_sql(name='sensors', con=conn, if_exists=if_exists, index=False)


def read_db(db_name):
    with sqlite3.connect(db_name) as conn:
        df = pd.read_sql('SELECT * FROM sensors', con=conn, parse_dates=['time'])
    return df


def get_last_readings(df_one_sensor):
    return df_one_sensor.loc[df_one_sensor.time.idxmax()]


all_esp_data(urls=URLS, db_name=DB_NAME, if_exists='replace')
sched = BackgroundScheduler(daemon=True)
sched.add_job(all_esp_data, kwargs={'urls': URLS}, trigger='interval', minutes=10)
sched.start()


@app.route("/")
def hello():
    return "стартовая страница"


@app.route("/data")  # запрос для датчика температуры
def show_last_data():
    df = read_db(db_name=DB_NAME)
    return df.groupby('sensor_name').apply(get_last_readings).to_html()


if __name__ == "__main__":
    app.run(host='172.20.10.7')