import datetime
import json
import sqlite3
from typing import List

import requests
from flask import Flask
from apscheduler.schedulers.background import BackgroundScheduler
import pandas as pd
app = Flask(__name__)

URLS = ['http://172.20.10.6']


def one_esp_data(url: str):
    base_info = json.loads(requests.get(url).text)
    poss_datas = [data_name for data_name in base_info['data'].split(';') if data_name != '']
    res = {}
    for data_name in poss_datas:
        res[data_name] = float(requests.get(f"{url}/{data_name}").text)
    res['time'] = datetime.datetime.now()
    res['sensor_name'] = base_info['sensor_name']
    return res


def all_esp_data(urls: List[str], if_exists: str = 'append'):
    all_res = []
    for url in urls:
        all_res.append(one_esp_data(url=url))
    if len(all_res) > 0:
        un_data = pd.DataFrame(all_res)
        with sqlite3.connect('smrh.db') as conn:
            un_data.to_sql(name='sensors', con=conn, if_exists=if_exists, index=False)


all_esp_data(urls=URLS, if_exists='replace')
sched = BackgroundScheduler(daemon=True)
sched.add_job(all_esp_data, kwargs={'urls': URLS}, trigger='interval', minutes=1)
sched.start()


@app.route("/")
def hello():
    return "стартовая страница"


@app.route("/data")  # запрос для датчика температуры
def push_new_temp():
    # t_bedroom = requests.get('http://192.168.1.207/temp')
    # h_bedroom = requests.get('http://192.168.1.207/humidity')
    # t_balcony = requests.get('http://192.168.1.109/temp')
    # h_balcony = requests.get('http://192.168.1.109/humidity')
    # df = pd.DataFrame([[t_bedroom.text, h_bedroom.text],
    #                    [t_balcony.text, h_balcony.text]],
    #                   index=['bedroom', 'balcony'],
    #                   columns=['temp', 'humidity'])
    # return df.to_html()
    return 'wait'


if __name__ == "__main__":
    app.run(host='172.20.10.7')
