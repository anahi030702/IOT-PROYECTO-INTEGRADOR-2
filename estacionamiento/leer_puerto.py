from datetime import datetime
from sensor import Sensor

import serial
import time
import json

from conectToDb import ConectionDb


class puertoSerial:
    def __init__(self):
        self.port = 'COM7'
        self.baudrate = 9600
        self.timeout = 0
        self.sensores = []
        self.accesos = []
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
                    fecha = datetime.now().strftime('%d-%m-%Y %H:%M:%S')
                    parts = line.split(':')

                    if self.db.conectar_mongo():
                        if "RF" in parts[0]:
                            sensor = Sensor(fecha)
                            res = self.db.updateone({ "usuarios-rfid.RFID" : parts[1]}, { "$push" : { "usuarios-rfid.$.accesos" : sensor.dict()}})
                            print(res)
                        else:
                            sensor = Sensor(parts[0], parts[1], fecha)
                            res = self.db.updateone({"nombre": "estacionamiento juarez" }, {"$set": {"sensores": sensor.dict()}})
                            print(res)
                    else:
                        if "RF" in parts[0]:
                            sensor = Sensor(fecha)
                            self.accesos.append(sensor.dict())
                            self.document("accesos", self.accesos)

                        else:
                            sensor = Sensor(parts[0], parts[1], fecha)
                            self.sensores.append(sensor.dict())
                            self.document("sensores", self.sensores)
                        print("GUARDADO LOCALMENTE HASTA QUE SE RESTABLEZCA LA COMUNICACION CON LA BD")


        except KeyboardInterrupt:
            print("Lectura interrumpida.")

        finally:
            ser.close()  # Cierra el puerto serial al finalizar

    def document(self, tipo, data):
        json_object = json.dumps(data, indent=4)

        with open(f"{tipo}.json", "w") as outfile:
            outfile.write(json_object)
        return "ok"

    def leer_doc(self, tipo):
        with open(f"{tipo}.json", 'r') as json_File:
            data = json.load(json_File)

        res = self.iterar_archivo(data)
        return res

    def iterar_archivo(self, data):
        valores = []

        for doc in data:
            valores.append(doc)
        return valores

    def checkDocs(self):
        if self.db.conectar_mongo:
            accesos = self.leer_doc("accesos")
            if accesos:
                self.accesos = accesos
                #debo hacer una funcion de push para agregar estos nuevos valores al arreglo de accesos
                self.db.create(self.accesos, 2)

            sensores = self.leer_doc("sensores")
            if sensores:
                self.sensores = sensores
                self.db.create(self.sensores, 2)




if __name__ == "__main__":
    puertoSerial().checkDocs()