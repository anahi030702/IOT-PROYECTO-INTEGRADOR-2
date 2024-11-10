import json

class Sensor:
    def __init__(self, clave=None, valor= None, fecha = None):
        self.clave = clave
        self.valor = valor
        self.fecha = fecha

    def dict(self):
        return { self.clave: self.valor, "fecha": self.fecha}

