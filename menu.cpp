#include "menu.h"
#include "Ciudadano.h"
#include "CuckooHashing.h"
#include <iostream>
#include <fstream>
#include <string>

// Función para insertar un ciudadano
void insertarCiudadano(CuckooHashing& hashTable) {
    Ciudadano ciudadano;
    std::cout << "\n--- Insertar Ciudadano ---\n";
    std::cin.ignore();
    std::cout << "DNI (8 dígitos): ";
    std::cin.getline(ciudadano.dni, 20); // Leer DNI como char[]

    if (std::strlen(ciudadano.dni) != 8) {
        std::cout << "Error: El DNI debe tener 8 dígitos.\n";
        return;
    }

    std::cout << "DNI (8 dígitos): ";
    std::cin.getline(ciudadano.dni, 20); // Usar std::cin.getline para char[]

    std::cout << "Nombres: ";
    std::cin.getline(ciudadano.nombres, 50);

    std::cout << "Apellidos: ";
    std::cin.getline(ciudadano.apellidos, 50);

    std::cout << "Nacionalidad: ";
    std::cin.getline(ciudadano.nacionalidad, 20);

    std::cout << "Lugar de Nacimiento: ";
    std::cin.getline(ciudadano.lugarNacimiento, 50);

    std::cout << "Departamento: ";
    std::cin.getline(ciudadano.direccion.departamento, 50);

    std::cout << "Provincia: ";
    std::cin.getline(ciudadano.direccion.provincia, 50);

    std::cout << "Ciudad: ";
    std::cin.getline(ciudadano.direccion.ciudad, 50);

    std::cout << "Distrito: ";
    std::cin.getline(ciudadano.direccion.distrito, 50);

    std::cout << "Teléfono: ";
    std::cin.getline(ciudadano.telefono, 15);

    std::cout << "Correo: ";
    std::cin.getline(ciudadano.correo, 50);

    std::cout << "Estado Civil: ";
    std::cin.getline(ciudadano.estadoCivil, 15);


    if (hashTable.insertar(ciudadano)) {
        std::cout << "Ciudadano insertado con éxito.\n";
    } else {
        std::cout << "Error: No se pudo insertar el ciudadano.\n";
    }
}

// Función para buscar un ciudadano
void buscarCiudadano(CuckooHashing& hashTable) {
    std::cout << "\n--- Buscar Ciudadano ---\n";
    std::cout << "DNI del ciudadano a buscar: ";
    std::string dni;
    std::cin >> dni;

    if (dni.length() != 8) {
        std::cout << "Error: El DNI debe tener 8 dígitos.\n";
        return;
    }

    auto resultado = hashTable.buscar(dni);
    if (resultado.has_value()) {
        Ciudadano ciudadano = resultado.value();
        std::cout << "Ciudadano encontrado:\n";
        std::cout << "DNI: " << ciudadano.dni << "\n";
        std::cout << "Nombres: " << ciudadano.nombres << "\n";
        std::cout << "Apellidos: " << ciudadano.apellidos << "\n";
        std::cout << "Nacionalidad: " << ciudadano.nacionalidad << "\n";
        std::cout << "Lugar de Nacimiento: " << ciudadano.lugarNacimiento << "\n";
        std::cout << "Dirección: " << ciudadano.direccion.departamento << ", "
                  << ciudadano.direccion.provincia << ", " << ciudadano.direccion.ciudad
                  << ", " << ciudadano.direccion.distrito << "\n";
        std::cout << "Teléfono: " << ciudadano.telefono << "\n";
        std::cout << "Correo: " << ciudadano.correo << "\n";
        std::cout << "Estado Civil: " << ciudadano.estadoCivil << "\n";
    } else {
        std::cout << "Ciudadano no encontrado.\n";
    }
}

// Función para eliminar un ciudadano
void eliminarCiudadano(CuckooHashing& hashTable) {
    std::cout << "\n--- Eliminar Ciudadano ---\n";
    std::cout << "DNI del ciudadano a eliminar: ";
    std::string dni;
    std::cin >> dni;

    if (dni.length() != 8) {
        std::cout << "Error: El DNI debe tener 8 dígitos.\n";
        return;
    }

    if (hashTable.eliminar(dni)) {
        std::cout << "Ciudadano eliminado con éxito.\n";
    } else {
        std::cout << "Ciudadano no encontrado.\n";
    }
}

// Función para guardar la tabla hash
void guardarTabla(CuckooHashing& hashTable) {
    std::cout << "\n--- Guardar Tabla Hash ---\n";
    std::cout << "Ingrese el nombre del archivo para guardar: ";
    std::string archivo;
    std::cin >> archivo;

    try {
        hashTable.guardarTabla(archivo);
        std::cout << "Tabla hash guardada en " << archivo << "\n";
    } catch (const std::exception& e) {
        std::cout << "Error al guardar la tabla: " << e.what() << "\n";
    }
}

// Función para cargar la tabla hash
void cargarTabla(CuckooHashing& hashTable) {
    std::cout << "\n--- Cargar Tabla Hash ---\n";
    std::cout << "Ingrese el nombre del archivo para cargar: ";
    std::string archivo;
    std::cin >> archivo;

    try {
        hashTable.cargarTablaDesdeBinario(archivo);
        std::cout << "Tabla hash cargada desde " << archivo << "\n";
    } catch (const std::exception& e) {
        std::cout << "Error al cargar la tabla: " << e.what() << "\n";
    }
}

// Mostrar el menú principal
void mostrarMenu(CuckooHashing& hashTable) {
    int opcion;
    do {
        std::cout << "\n--- Menu Principal ---\n";
        std::cout << "1. Insertar Ciudadano\n";
        std::cout << "2. Buscar Ciudadano\n";
        std::cout << "3. Eliminar Ciudadano\n";
        std::cout << "4. Guardar Tabla Hash\n";
        std::cout << "5. Cargar Tabla Hash\n";
        std::cout << "6. Salir\n";
        std::cout << "Selecciona una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                insertarCiudadano(hashTable);
                break;
            case 2:
                buscarCiudadano(hashTable);
                break;
            case 3:
                eliminarCiudadano(hashTable);
                break;
            case 4:
                guardarTabla(hashTable);
                break;
            case 5:
                cargarTabla(hashTable);
                break;
            case 6:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opción inválida. Intenta de nuevo.\n";
                break;
        }
    } while (opcion != 6);
}
