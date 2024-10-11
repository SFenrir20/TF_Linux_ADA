# Proyecto de Estructura de Datos Avanzado (EDA)

## Descripción del Proyecto

Este proyecto tiene como objetivo desarrollar una estructura de datos eficiente para almacenar y gestionar la información de ciudadanos peruanos registrados en una nueva entidad del estado. La estructura debe ser capaz de manejar al menos **33 millones de registros**, con operaciones eficientes de **búsqueda, inserción y eliminación**. No se utilizará una base de datos, sino que la información se almacenará y recuperará directamente del disco utilizando técnicas avanzadas de almacenamiento.

### Funcionalidades
  - **Registro de ciudadanos:** Almacenamiento de datos como el **DNI, nombre completo, nacionalidad, lugar de nacimiento, dirección, teléfono, correo electrónico, y estado civil.**
  - **Búsqueda por DNI:** Permite buscar y recuperar los datos de un ciudadano a partir de su DNI. Si el ciudadano no existe, muestra un mensaje de advertencia.
  - **Almacenamiento en disco:** Toda la información es persistente y puede ser recuperada del disco la próxima vez que se inicie el programa.
  - **Eficiencia y escalabilidad:** El sistema está diseñado para escalar más allá de los 33 millones de registros, y se realizará un análisis de la complejidad algorítmica y un benchmarking de las operaciones principales.
    
### Tecnología Utilizada
  - Lenguaje: C++
  - IDE: CLion
  - Librerías:
        Boost: Se utiliza Boost para manejo de bibliotecas avanzadas, como funciones auxiliares para la simulación de datos y manejo de archivos.

### Datos de los Estudiantes
 - Nombre: Santiago Salazar
 - Curso: Estructura de Datos Avanzado (EDA)
 - Universidad: Universidad San Ignacio de Loyola

### Especificaciones Técnicas
  -  El programa genera números de DNI aleatorios y simula los demás datos (nombre, dirección, etc.) de manera automática.
  -  La estructura debe ser capaz de manejar crecimientos en el número de registros, asegurando que se puede almacenar información de millones de ciudadanos sin perder eficiencia.
  -  El programa guarda los datos en el disco y los recupera al iniciar, permitiendo búsquedas en memoria sin necesidad de regenerar todos los datos.

### Análisis de Complejidad
Una vez que se alcance el límite de 33 millones de registros, se evaluará la complejidad algorítmica de las siguientes operaciones:
  -  Búsqueda: Se analizará el tiempo que toma buscar un ciudadano por su DNI.
  -  Inserción: Se evaluará el tiempo y espacio necesarios para agregar nuevos registros.
  -  Eliminación: Se medirán los costos temporales y espaciales de eliminar registros.

Además, se analizarán las complejidades en términos de Big O para cada operación mencionada.
