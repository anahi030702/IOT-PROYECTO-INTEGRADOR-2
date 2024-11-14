import json

from arreglo import Arreglo


class Sensor(Arreglo):
    def __init__(self, tipo=None, valor= None, fecha = None):
        if tipo is not None:
            self.tipo = tipo
            self.valor = valor
            self.fecha = fecha
            self._is_array = False
        else:
            self._is_array = True
            super().__init__()

    def __str__(self):
        if self._is_array:
            return super().__str__()
        else:
            return f"Sensor(tipo={self.tipo}, valor={self.valor}, fecha={self.fecha})"


    def dict(self):
        if self._is_array:
            return [arreglo.dict() for arreglo in self.arreglos]
        else:
            return { "tipo" : self.tipo, "valor": self.valor, "fecha": self.fecha }

    def iterar_archivo(self, data):
        sensores = []

        for doc in data:
            sensor = Sensor(doc["tipo"], doc["valor"], doc["fecha"], doc["estacionamiento"])
            sensores.append(sensor)
        self.arreglos = sensores
        return sensores


if __name__ == "__main__":
    ses = Sensor()
    se = Sensor("mq2", 45, "25/11/2024", "654156465")
    se1 = Sensor("mq2", 45, "25/11/2024", "654156465")
    ses.agregar(se)
    ses.agregar(se1)
    print(ses.dict())