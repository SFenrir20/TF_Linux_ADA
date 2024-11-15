//
// Created by fenrirdev on 13/11/24.
//

#include "CuckooHashing.h"
#include <fstream>
#include <sstream>

// Constructor con tamaño de tablas y límite de intentos para evitar ciclos
CuckooHashing::CuckooHashing(size_t size) : tabla1(size), tabla2(size), maxIntentos(10) {
    std::ifstream archivo("/home/fenrirdev/Documentos/EDA/TF_Linux_EDA/Generador/ciudadanos.csv");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir archivo" << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        Ciudadano ciudadano;

        std::getline(ss, ciudadano.dni, ',');
        std::getline(ss, ciudadano.nombres, ',');
        std::getline(ss, ciudadano.apellidos, ',');
        std::getline(ss, ciudadano.nacionalidad, ',');
        std::getline(ss, ciudadano.lugarNacimiento, ',');

        std::getline(ss, ciudadano.direccion.departamento, ',');
        std::getline(ss, ciudadano.direccion.provincia, ',');
        std::getline(ss, ciudadano.direccion.ciudad, ',');
        std::getline(ss, ciudadano.direccion.distrito, ',');


        std::getline(ss, ciudadano.telefono, ',');
        std::getline(ss, ciudadano.correo, ',');
        std::getline(ss, ciudadano.estadoCivil, ',');

        insertar(ciudadano); // Insertamos el ciudadano en la tabla hash
    }

    archivo.close();
}



// Funciones hash (simple para ejemplo, puedes mejorarlas)
size_t CuckooHashing::hash1(const std::string& dni) {
    return std::hash<std::string>{}(dni) % tabla1.size();
}

size_t CuckooHashing::hash2(const std::string& dni) {
    return (std::hash<std::string>{}(dni) / tabla1.size()) % tabla2.size();
}

// Insertar un ciudadano con cuckoo hashing
bool CuckooHashing::insertar(const Ciudadano& ciudadano) {
    Ciudadano current = ciudadano;
    for (size_t intentos = 0; intentos < maxIntentos; ++intentos) {
        size_t pos1 = hash1(current.dni);
        if (!tabla1[pos1].has_value()) {
            tabla1[pos1] = current;
            return true;
        }

        std::swap(current, tabla1[pos1].value());

        size_t pos2 = hash2(current.dni);
        if (!tabla2[pos2].has_value()) {
            tabla2[pos2] = current;
            return true;
        }

        std::swap(current, tabla2[pos2].value());
    }

    rehash();
    return insertar(current);
}

void CuckooHashing::guardarDatos() {
    std::ofstream archivo("/home/fenrirdev/Documentos/EDA/TF_Linux_EDA/Generador/ciudadanos.csv");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir ciudadanos.csv para guardar datos" << std::endl;
        return;
    }

    archivo << "DNI,Nombres,Apellidos,Nacionalidad,LugarNacimiento,Direccion,Telefono,Email,EstadoCivil\n";

    for (const auto& entrada : tabla1) {
        if (entrada.has_value()) {
            const Ciudadano& ciudadano = entrada.value();
            archivo << ciudadano.dni << ","
                              << ciudadano.nombres << ","
                              << ciudadano.apellidos << ","
                              << ciudadano.nacionalidad << ","
                              << ciudadano.lugarNacimiento << ","
                              << ciudadano.direccion.departamento << ","
                              << ciudadano.direccion.provincia << ","
                              << ciudadano.direccion.ciudad << ","
                              << ciudadano.direccion.distrito << ","
                              << ciudadano.telefono << ","
                              << ciudadano.correo << ","
                              << ciudadano.estadoCivil << "\n";
        }
    }

    for (const auto& entrada : tabla2) {
        if (entrada.has_value()) {
            const Ciudadano& ciudadano = entrada.value();
            archivo << ciudadano.dni << ","
                    << ciudadano.nombres << ","
                    << ciudadano.apellidos << ","
                    << ciudadano.nacionalidad << ","
                    << ciudadano.lugarNacimiento << ","
                    << ciudadano.direccion.departamento << ","
                    << ciudadano.direccion.provincia << ","
                    << ciudadano.direccion.ciudad << ","
                    << ciudadano.direccion.distrito << ","
                    << ciudadano.telefono << ","
                    << ciudadano.correo << ","
                    << ciudadano.estadoCivil << "\n";
        }
    }

    archivo.close();
}


// Buscar un ciudadano por DNI
std::optional<Ciudadano> CuckooHashing::buscar(const std::string& dni) {
    size_t pos1 = hash1(dni);
    if (tabla1[pos1].has_value() && tabla1[pos1]->dni == dni) {
        return tabla1[pos1];
    }

    size_t pos2 = hash2(dni);
    if (tabla2[pos2].has_value() && tabla2[pos2]->dni == dni) {
        return tabla2[pos2];
    }

    return std::nullopt;
}

// Eliminar un ciudadano por DNI
bool CuckooHashing::eliminar(const std::string& dni) {
    size_t pos1 = hash1(dni);
    if (tabla1[pos1].has_value() && tabla1[pos1]->dni == dni) {
        tabla1[pos1].reset();
        return true;
    }

    size_t pos2 = hash2(dni);
    if (tabla2[pos2].has_value() && tabla2[pos2]->dni == dni) {
        tabla2[pos2].reset();
        return true;
    }

    return false;
}

// Rehash: duplicar el tamaño de la tabla y reinsertar elementos
void CuckooHashing::rehash() {
    std::vector<std::optional<Ciudadano>> oldTabla1 = tabla1;
    std::vector<std::optional<Ciudadano>> oldTabla2 = tabla2;
    tabla1.resize(tabla1.size() * 2);
    tabla2.resize(tabla2.size() * 2);

    for (const auto& ciudadano : oldTabla1) {
        if (ciudadano.has_value()) {
            insertar(ciudadano.value());
        }
    }

    for (const auto& ciudadano : oldTabla2) {
        if (ciudadano.has_value()) {
            insertar(ciudadano.value());
        }
    }
}
