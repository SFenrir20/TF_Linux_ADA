#include <iostream>
#include "CuckooHashing.h"
#include "menu.h"

int main() {
    size_t size = 200;
    CuckooHashing tablaHash(size); // Tamaño de 33 millones de registros

    // Cargar datos desde el archivo CSV al iniciar el programa
    //cargarDatosDesdeCSV("D:\\Repos\\TF_Linux_EDA\\Generador\\ciudadanos.csv", tablaHash);

    mostrarMenu(tablaHash);

    tablaHash.guardarDatos();

    return 0;
}
