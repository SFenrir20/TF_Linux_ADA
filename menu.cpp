//
// Created by fenrirdev on 13/11/24.
//

#include "menu.h"
#include "Ciudadano.h"
#include "CuckooHashing.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


void mostrarMenu(CuckooHashing& hashTable) {
    int opcion;
    do {
        std::cout << "\n--- Menu Principal ---\n";
        std::cout << "1. Insertar Ciudadano\n";
        std::cout << "2. Buscar Ciudadano\n";
        std::cout << "3. Eliminar Ciudadano\n";
        std::cout << "4. Salir\n";
        std::cout << "Selecciona una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                Ciudadano ciudadano;
                std::cout << "DNI: "; std::cin >> ciudadano.dni;
                std::cout << "Nombres: "; std::cin >> ciudadano.nombres;
                std::cout << "Apellidos: "; std::cin >> ciudadano.apellidos;
                std::cout << "Nacionalidad: "; std::cin >> ciudadano.nacionalidad;
                std::cout << "Lugar de Nacimiento: "; std::cin >> ciudadano.lugarNacimiento;

                // Capturar los datos de Direccion uno por uno
                std::cout << "Departamento: "; std::cin >> ciudadano.direccion.departamento;
                std::cout << "Provincia: "; std::cin >> ciudadano.direccion.provincia;
                std::cout << "Ciudad: "; std::cin >> ciudadano.direccion.ciudad;
                std::cout << "Distrito: "; std::cin >> ciudadano.direccion.distrito;

                std::cout << "Teléfono: "; std::cin >> ciudadano.telefono;
                std::cout << "Correo: "; std::cin >> ciudadano.correo;
                std::cout << "Estado Civil: "; std::cin >> ciudadano.estadoCivil;

                if (hashTable.insertar(ciudadano)) {
                    std::cout << "Ciudadano insertado con éxito.\n";
                } else {
                    std::cout << "Error al insertar ciudadano.\n";
                }
                break;
            }
            case 2: {
                std::string dni;
                std::cout << "DNI del ciudadano a buscar: ";
                std::cin >> dni;

                auto resultado = hashTable.buscar(dni);
                if (resultado.has_value()) {
                    std::cout << "Ciudadano encontrado:\n";
                    std::cout << "DNI: " << resultado->dni << "\n";
                    std::cout << "Nombres: " << resultado->nombres << "\n";
                    std::cout << "Apellidos: " << resultado->apellidos << "\n";
                } else {
                    std::cout << "Ciudadano no encontrado.\n";
                }
                break;
            }
            case 3: {
                std::string dni;
                std::cout << "DNI del ciudadano a eliminar: ";
                std::cin >> dni;

                if (hashTable.eliminar(dni)) {
                    std::cout << "Ciudadano eliminado con éxito.\n";
                } else {
                    std::cout << "Ciudadano no encontrado.\n";
                }
                break;
            }
            case 4:
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Opción inválida, intenta de nuevo.\n";
                break;
        }
    } while (opcion != 4);
}

void cargarDatosDesdeCSV(const std::string& nombreArchivo, CuckooHashing& tablaHash) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    std::string linea;
    std::getline(archivo, linea); // Leer la primera línea (encabezado)

    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string dni, nombres, apellidos, nacionalidad, lugarNacimiento;
        std::string departamento, provincia, ciudad, distrito;
        std::string telefono, correo, estadoCivil;

        // Leer cada campo separado por coma
        std::getline(ss, dni, ',');
        std::getline(ss, nombres, ',');
        std::getline(ss, apellidos, ',');
        std::getline(ss, nacionalidad, ',');
        std::getline(ss, lugarNacimiento, ',');

        // Leer los componentes de Direccion
        std::getline(ss, departamento, ',');
        std::getline(ss, provincia, ',');
        std::getline(ss, ciudad, ',');
        std::getline(ss, distrito, ',');

        std::getline(ss, telefono, ',');
        std::getline(ss, correo, ',');
        std::getline(ss, estadoCivil, ',');

        // Crear el objeto Direccion
        Direccion direccion = {departamento, provincia, ciudad, distrito};

        // Crear el objeto Ciudadano con el objeto Direccion
        Ciudadano ciudadano(dni, nombres, apellidos, nacionalidad, lugarNacimiento, direccion, telefono, correo, estadoCivil);

        // Insertar el ciudadano en la tabla hash usando el DNI como clave
        tablaHash.insertar(ciudadano);
    }

    archivo.close();
    std::cout << "Datos cargados desde " << nombreArchivo << " exitosamente." << std::endl;
}