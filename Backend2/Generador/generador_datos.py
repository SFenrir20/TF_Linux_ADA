import os
import random
import struct


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

# Estructura binaria para un ciudadano (DNI, nombre, apellido, etc.)
CIUDADANO_STRUCT = struct.Struct("20s 50s 50s 20s 50s 200s 15s 50s 15s")


# Función para crear el índice binario
def crear_indice_bin(indice, archivo_indice):
    INDICE_STRUCT = struct.Struct("20s 50s I")
    with open(archivo_indice, mode='wb') as index_file:
        for dni, archivo, posicion in indice:
            index_file.write(INDICE_STRUCT.pack(
                dni.encode('utf-8'), archivo.encode('utf-8'), posicion
            ))
    print(f"Índice guardado en {archivo_indice}")


# Generar registros de ciudadanos con DNIs correlativos
def generar_ciudadanos_bin(num_registros, archivo_salida_prefix):
    # Dividir en bloques de 10 millones
    registros_por_archivo = 10_000_000
    indice = []

    # Crear los archivos binarios
    for i in range((num_registros // registros_por_archivo) + 1):
        # Determinar el rango de registros para este archivo
        archivo_bin = f"{archivo_salida_prefix}_{i + 1}.bin"
        inicio = i * registros_por_archivo
        fin = min((i + 1) * registros_por_archivo, num_registros)
        if inicio >= num_registros:
            break

        with open(archivo_bin, mode='wb') as bin_file:
            for j in range(inicio, fin):
                # Generar un ciudadano aleatorio
                dni = str(10000000 + j).encode('utf-8')
                nombre = random.choice(nombres).encode('utf-8')
                apellido = random.choice(apellidos).encode('utf-8')
                nacionalidad = random.choice(nacionalidades).encode('utf-8')
                lugar_nacimiento = random.choice(lugares_nacimiento).encode('utf-8')
                direccion = random.choice(direcciones).encode('utf-8')
                telefono = f"+51 {random.randint(900000000, 999999999)}".encode('utf-8')
                correo = f"{nombre.decode().lower()}.{apellido.decode().lower()}@ejemplo.com".encode('utf-8')
                estado_civil = random.choice(estados_civiles).encode('utf-8')

                # Escribir el registro en el archivo binario
                bin_file.write(CIUDADANO_STRUCT.pack(
                    dni, nombre, apellido, nacionalidad, lugar_nacimiento,
                    direccion, telefono, correo, estado_civil
                ))

                # Guardar en el índice: [DNI, archivo, posición]
                indice.append((dni.decode('utf-8'), archivo_bin, j - inicio))

    # Crear el índice en binario después de generar todos los registros
    crear_indice_bin(indice, f"{archivo_salida_prefix}_indice.bin")
    print(f"Generación de datos completa: {num_registros} registros guardados.")


# Llamada a la función
generar_ciudadanos_bin(1_000_000, "prueba_ciudadanos")
