from pymongo.synchronous.client_session import SessionOptions

from sensor import Sensor
from arreglo import Arreglo
from conectToDb import ConectionDb
import json
from bson import ObjectId

class Estacionamiento(Arreglo):
    def __init__(self, noEs=None, nombre=None, ubicacion=None):
        if nombre is not None:
            self.noEs = noEs
            self.nombre = nombre
            self.ubicacion = ubicacion
            self.sensores = Sensor()
            self._is_array = False
        else:
            super().__init__()
            self._is_array = True

    def __str__(self):
        if self._is_array:
            return super().__str__()
        else:
            return f"Estacionamiento(no.estacionamiento={self.noEs}, nombre={self.nombre}, ubicacion={self.ubicacion}, sensores={self.sensores})"

    def dict(self):
        if self._is_array:
            return [arreglo.dict() for arreglo in self.arreglos]
        else:
            return { "no. estacionamiento": self.noEs, "nombre" : self.nombre, "ubicacion": self.ubicacion, "sensores": self.sensores.dict() }

    def document(self, data):
            json_object = json.dumps(data, indent=4)

            with open(f"estacionamientos.json", "w") as outfile:
                outfile.write(json_object)
            return "ok"

    def leer_doc(self):
        with open('estacionamientos.json', 'r') as json_File:
            data = json.load(json_File)

        estacionamientos = self.iterar_archivo(data)
        return estacionamientos


    def iterar_archivo(self, data):
        estacionamientos = []

        for doc in data:
            sensores = Sensor()
            estacionamiento = Estacionamiento(doc["no. estacionamiento"], doc["nombre"], doc["ubicacion"])
            sensores.iterar_archivo(doc["sensores"])
            estacionamiento.sensores=sensores
            estacionamientos.append(estacionamiento)

        self.arreglos = estacionamientos
        return estacionamientos

    #hacer que los sensores que se le manden se actualicen en mongo o en el archivo json segun la conectividad con mongo
    def actualizarSensores(self, data):
        db = ConectionDb()
        if db.conectar_mongo():
            res = db.updateone({"_id": ObjectId("6728053923ad77d8021b8337")}, {"$push" : {"sensores": data}})
            print(res)





if __name__ == "__main__":
    estas = Estacionamiento()
    estas.leer_doc()
    esta = estas[0]
    se = Sensor("mq1", 45, "15/25/2024", 1)
    esta.sensores.agregar(se)
    print(esta)




