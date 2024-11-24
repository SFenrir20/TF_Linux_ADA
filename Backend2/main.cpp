#include <iostream>
#include "CuckooHashing.h"
#include "menu.h"

int main() {
    try {
        // Inicializar la tabla hash con un tamaño base
        size_t size = 200; // Puedes ajustar este tamaño si se requiere
        CuckooHashing tablaHash(size);

        // Mostrar el menú principal
        mostrarMenu(tablaHash);

        // Guardar los datos al salir del programa
        std::string archivoSalida;
        std::cout << "\n¿Desea guardar los datos de la tabla hash antes de salir? (s/n): ";
        char opcion;
        std::cin >> opcion;

        if (opcion == 's' || opcion == 'S') {
            std::cout << "Ingrese el nombre del archivo de salida: ";
            std::cin >> archivoSalida;
            tablaHash.guardarTabla(archivoSalida);
            std::cout << "Datos guardados en el archivo: " << archivoSalida << "\n";
        } else {
            std::cout << "Datos no guardados.\n";
        }

        std::cout << "Programa finalizado.\n";
        return 0;

    } catch (const std::exception& e) {
        // Capturar cualquier error inesperado
        std::cerr << "Error: " << e.what() << "\n";
        return 1; // Retornar código de error
    }
}
