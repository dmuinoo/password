# -*- coding: utf-8 -*-
import time
import argparse
import sqlite3

import Adafruit_BMP.BMP085 as BMP085

sensor = BMP085.BMP085()

con_db = sqlite3.connect('water.db')
cursor = con_db.cursor()

def insert_into_db(pos_x, pos_y):
    timestamp = int(time.time())
    pressure = '{0:0.2f}'.format(sensor.read_pressure())
    temp = '{0:0.2f}'.format(sensor.read_temperature())

    data = (timestamp, pressure, temp, pos_x, pos_y)
    query = ('INSERT INTO watertb VALUES (?,?,?,?,?)')

    cursor.execute(query, data)
    con_db.commit()

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description = 'Inserts field data into a sqlite db.')
    parser.add_argument('pos_x', metavar = 'field_x')
    parser.add_argument('pos_y', metavar = 'field_y')
    args = vars(parser.parse_args())
    insert_into_db(args['pos_x'], args['pos_y'])
