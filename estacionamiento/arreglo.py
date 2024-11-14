import json
import os

class Arreglo:
    def __init__(self):
        self.arreglos = []

    def __str__(self):
        return '\n'.join(str(arreglo) for arreglo in self.arreglos)
        # return json.dumps(self.arreglos, indent=4)

    # Métodos para cuando funciona como arreglo
    # regresa el valor que se encuentra en el indice especificado
    def __getitem__(self, index):
        return self.arreglos[index]

    # edita el valor del indice que se especifique
    def __setitem__(self, index, valor):
        self.arreglos[index] = valor

    # regresa el numero de elementos que tiene el array
    def __len__(self):
        return len(self.arreglos)

    # Elimina el elmento del indice que le indiquemos
    def __delitem__(self, index):
        del self.arreglos[index]

    # agrega al array el elemento que se le pasa
    def agregar(self, valor):
        self.arreglos.append(valor)

    def buscar_indice(self, valor):
        try:
            return self.arreglos.index(valor)
        except ValueError:
            return -1  # Devuelve -1 si el valor no se encuentra

    # def document(self, tipo, data):
    #         json_object = json.dumps(data, indent=4)
    #
    #         with open(f"{tipo}.json", "w") as outfile:
    #             outfile.write(json_object)
    #         return "ok"



# #otras maneras de usar los metodos magicos
# #metodo __len__
# len(arreglo)
# #metodo __getitem__
# arreglo[0]
# #metodo __setitem__
# arreglo[0] = Alumno("Alberto", "Gonzalez", "Contreras", "AGCO050906MCLLLN04", "2252930")
# #metodo __delitem
# del arreglo[0]
