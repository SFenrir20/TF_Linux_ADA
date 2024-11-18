import os
import csv
import random


# Función para cargar los datos desde un archivo CSV a una lista
def cargar_datos(archivo):
    with open(archivo, mode='r', encoding='utf-8') as f:
        return [linea.strip() for linea in f]


# Cargar los datos desde los archivos CSV
nombres = cargar_datos("D:\\Repos\\TF_Linux_EDA\\Generador\\Data\\nombres.csv")
apellidos = cargar_datos("D:\\Repos\\TF_Linux_EDA\\Generador\\Data\\apellidos.csv")
direcciones = cargar_datos("D:\\Repos\\TF_Linux_EDA\\Generador\\Data\\direccion.csv")

# Listas fijas para otros datos
nacionalidades = ["Peruano"]
lugares_nacimiento = ["Lima", "Arequipa", "Cusco", "Trujillo", "Piura"]
estados_civiles = ["Soltero", "Casado", "Divorciado", "Viudo"]


# Generar registros de ciudadanos con DNIs correlativos
def generar_ciudadanos(num_registros, archivo_salida):
    # Eliminar el archivo si ya existe, para evitar duplicados
    if os.path.exists(archivo_salida):
        os.remove(archivo_salida)  # Eliminar el archivo existente
        print(f"Archivo existente {archivo_salida} eliminado para evitar duplicados.")

    # Abrir el archivo en modo de escritura
    with open(archivo_salida, mode='w', newline='', encoding='utf-8') as archivo:
        escritor_csv = csv.writer(archivo, delimiter=';')


        for i in range(num_registros):
            # Asignar DNI correlativo empezando desde 10000000
            dni = str(10000000 + i)
            nombre = random.choice(nombres)
            apellido = random.choice(apellidos)
            nacionalidad = random.choice(nacionalidades)
            lugar_nacimiento = random.choice(lugares_nacimiento)
            direccion = random.choice(direcciones)
            telefono = f"+51 {random.randint(900000000, 999999999)}"
            correo = f"{nombre.lower()}.{apellido.lower()}@ejemplo.com"
            estado_civil = random.choice(estados_civiles)

            # Escribir el registro en el archivo CSV
            escritor_csv.writerow(
                [dni, nombre, apellido, nacionalidad, lugar_nacimiento, direccion, telefono, correo, estado_civil])

    print(f"Generación de datos completa: {num_registros} registros guardados en {archivo_salida}")


# Llamada a la función
generar_ciudadanos(3, "D:\\Repos\\TF_Linux_EDA\\Generador\\ciudadanos.csv")
