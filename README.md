# Proyecto de Estructura de Datos Avanzado (EDA)

[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
![GitHub contributors](https://img.shields.io/github/contributors/SFenrir20/TF_Linux_EDA)
![GitHub issues](https://img.shields.io/github/issues-raw/SFenrir20/TF_Linux_EDA)
![GitHub stars](https://img.shields.io/github/stars/SFenrir20/TF_Linux_EDA)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/SFenrir20/TF_Linux_EDA)
![GitHub All Releases](https://img.shields.io/github/downloads/SFenrir20/TF_Linux_EDA/total)
![GitHub last commit](https://img.shields.io/github/last-commit/SFenrir20/TF_Linux_EDA)

## Descripción del Proyecto

Este proyecto tiene como objetivo desarrollar una estructura de datos eficiente para almacenar y gestionar la información de ciudadanos peruanos registrados en una nueva entidad del estado. La estructura debe ser capaz de manejar al menos **33 millones de registros**, con operaciones eficientes de **búsqueda, inserción y eliminación**. No se utilizará una base de datos, sino que la información se almacenará y recuperará directamente del disco utilizando técnicas avanzadas de almacenamiento.


## Tabla de Contenidos :scroll:

- [Funcionalidades](#funcionalidades)
- [Tecnología Utilizada](#tecnología-utilizada)
- [Datos de los Estudiantes](#datos-de-los-estudiantes)
- [Especificaciones Técnicas](#especificaciones-técnicas)
- [Análisis de Complejidad](#análisis-de-complejidad)
- [Instalación](#instalación)
- [Uso](#uso)
- [Contribuciones](#contribuciones)
- [Licencia](#licencia)
- [Contacto](#contacto)
- [Institución](#institución)
- [Contribuyentes](#contribuyentes)
- [Dependencias](#dependencias)

## Funcionalidades
  - **Registro de ciudadanos:** Almacenamiento de datos como el **DNI, nombre completo, nacionalidad, lugar de nacimiento, dirección, teléfono, correo electrónico, y estado civil.**
  - **Búsqueda por DNI:** Permite buscar y recuperar los datos de un ciudadano a partir de su DNI. Si el ciudadano no existe, muestra un mensaje de advertencia.
  - **Almacenamiento en disco:** Toda la información es persistente y puede ser recuperada del disco la próxima vez que se inicie el programa.
  - **Eficiencia y escalabilidad:** El sistema está diseñado para escalar más allá de los 33 millones de registros, y se realizará un análisis de la complejidad algorítmica y un benchmarking de las operaciones principales.
    
## Tecnología Utilizada

- Lenguaje: [C++](https://www2.eii.uva.es/fund_inf/cpp/temas/1_introduccion/introduccion.html)
- IDE: [CLion](https://www.jetbrains.com/clion/promo/?source=google&medium=cpc&campaign=AMER_en_AMER_Clion_Branded&term=clion&content=489240779021&gad_source=1&gclid=CjwKCAjwmaO4BhAhEiwA5p4YL6VDq4959AtRPTpEnECGqIjYINPpxjSPGqXqbDFJu_ebBM6mVBBiPxoCwZMQAvD_BwE)
- Librerías:
  - [Boost](https://www.boost.org/): Se utiliza Boost para manejo de bibliotecas avanzadas, como funciones auxiliares para la simulación de datos y manejo de archivos.


### Datos de los Estudiantes
 - Nombre: Santiago Salazar
 - Curso: Estructura de Datos Avanzado (EDA)
 - Universidad: Universidad San Ignacio de Loyola

## Especificaciones Técnicas
  -  El programa genera números de DNI aleatorios y simula los demás datos (nombre, dirección, etc.) de manera automática.
  -  La estructura debe ser capaz de manejar crecimientos en el número de registros, asegurando que se puede almacenar información de millones de ciudadanos sin perder eficiencia.
  -  El programa guarda los datos en el disco y los recupera al iniciar, permitiendo búsquedas en memoria sin necesidad de regenerar todos los datos.

## Análisis de Complejidad
Una vez que se alcance el límite de 33 millones de registros, se evaluará la complejidad algorítmica de las siguientes operaciones:
  -  Búsqueda: Se analizará el tiempo que toma buscar un ciudadano por su DNI.
  -  Inserción: Se evaluará el tiempo y espacio necesarios para agregar nuevos registros.
  -  Eliminación: Se medirán los costos temporales y espaciales de eliminar registros.

Además, se analizarán las complejidades en términos de Big O para cada operación mencionada.

## Instalación :wrench:

Instrucciones sobre cómo instalar y ejecutar el proyecto.

## Uso :computer:

Instrucciones sobre cómo usar el proyecto o ejemplos de código.

## Contribuciones :handshake:

Si deseas contribuir a este proyecto, sigue estas pautas.

## Licencia :memo:

Este proyecto está licenciado bajo la Licencia MIT - consulta el archivo [LICENSE](LICENSE) para más detalles.

## Contacto :email:

Si tienes preguntas o comentarios, no dudes en comunicarte:

- **Nombre:** Santiago Salazar
- **Email:** luissantiagoblass@gmail.com
- **GitHub:** [SFenrir20](https://github.com/SFenrir20)

## Institución :mortar_board:

- **Universidad:** Universidad San Ignacio de Loyola
- **Curso:** Estructura de Datos Avanzado (EDA)
- **Semestre:** 7mo semestre.

## Contribuyentes :busts_in_silhouette:

- [Contribuyente 1](https://github.com/SFenrir20)
- [Contribuyente 2](https://github.com/Contributor2)
- [Contribuyente 3](https://github.com/Contributor3)
- [Contribuyente 4](https://github.com/Contributor4)
- [Contribuyente 5](https://github.com/Contributor5)

## Dependencias :link:

- [Boost](https://www.boost.org/)
