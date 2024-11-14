from datetime import datetime

from estacionamiento import Estacionamiento
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
        self.est = Estacionamiento()

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
                    sensor = Sensor(parts[0], parts[1], fecha)
                    self.est.actualizarSensores(sensor.dict())




        except KeyboardInterrupt:
            print("Lectura interrumpida.")

        finally:
            ser.close()  # Cierra el puerto serial al finalizar






if __name__ == "__main__":
    puertoSerial().leer_puerto()