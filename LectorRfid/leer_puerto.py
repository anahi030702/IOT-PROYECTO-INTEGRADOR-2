#!/usr/bin/env python3
import serial
import time
from bson import ObjectId


from conectToDb import ConectionDb


class puertoSerial:
    def __init__(self):
        self.port = 'COM9'
        self.baudrate = 9600
        self.timeout = 0
        self.db = ConectionDb()

    def leer_puerto(self):
        # Inicializa la conexión serial
        ser = serial.Serial(self.port, self.baudrate, timeout= self.timeout)

        # Espera un poco para que se establezca la conexión
        time.sleep(2)

        try:
            while True:
                if ser.in_waiting > 0:  # Verifica si hay datos disponibles para leer
                    line = ser.readline().decode('utf-8').rstrip()  # Lee la línea y decodifica
                    print(line)
                    self.actualizarSensor(line)

        except KeyboardInterrupt:
            print("Lectura interrumpida.")

        finally:
            ser.close()


    def actualizarSensor(self, data):
            res = self.db.updateone({"_id": ObjectId("673a970b8548904611656030"), "sensores.tipo": "RF-2"}, {"$set" : {"sensores.$.valor": data}})
            print(res)








if __name__ == "__main__":
    puertoSerial().leer_puerto()
