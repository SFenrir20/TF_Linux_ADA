//
// Created by fenrirdev on 13/11/24.
//

#include "CuckooHashing.h"

#include <cstdint>
#include <iostream>
#include <cstring>


CuckooHashing::CuckooHashing(size_t size)
    : tabla1(size), tabla2(size), maxIntentos(10) {}


// Funciones hash
size_t CuckooHashing::hash1(const std::string& dni) const {
    std::hash<std::string> hash_fn;
    return hash_fn(dni) % tabla1.size();
}

size_t CuckooHashing::hash2(const std::string& dni) const {
    std::hash<std::string> hash_fn;
    return (hash_fn(dni) / tabla1.size()) % tabla2.size();
}

// Insertar un ciudadano en la tabla hash
bool CuckooHashing::insertar(const Ciudadano& ciudadano) {
    Ciudadano current = ciudadano;

    for (size_t intentos = 0; intentos < maxIntentos; ++intentos) {
        size_t pos1 = hash1(current.dni);
        if (!tabla1[pos1].has_value()) {
            tabla1[pos1] = current;
            return true;
        }

        // Colisión en tabla1
        std::swap(current, tabla1[pos1].value());
        size_t pos2 = hash2(current.dni);

        if (!tabla2[pos2].has_value()) {
            tabla2[pos2] = current;
            return true;
        }

        // Colisión en tabla2
        std::swap(current, tabla2[pos2].value());
    }

    // Si no se pudo insertar, rehash y reintentar
    rehash();
    return insertar(current);
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

// Guardar tabla hash en un archivo binario
void CuckooHashing::guardarTabla(const std::string& archivoBinario) {
    std::ofstream file(archivoBinario, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para guardar la tabla hash.");
    }

    for (const auto& ciudadanoOpt : tabla1) {
        if (ciudadanoOpt.has_value()) {
            file.write(reinterpret_cast<const char*>(&ciudadanoOpt.value()), sizeof(Ciudadano));
        }
    }

    for (const auto& ciudadanoOpt : tabla2) {
        if (ciudadanoOpt.has_value()) {
            file.write(reinterpret_cast<const char*>(&ciudadanoOpt.value()), sizeof(Ciudadano));
        }
    }

    file.close();
    std::cout << "Tabla hash guardada en " << archivoBinario << "\n";
}

// Cargar tabla hash desde un archivo binario
void CuckooHashing::cargarTablaDesdeBinario(const std::string& archivoBinario) {
    std::ifstream file(archivoBinario, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo binario para cargar la tabla hash.");
    }

    Ciudadano ciudadano;
    while (file.read(reinterpret_cast<char*>(&ciudadano), sizeof(Ciudadano))) {
        insertar(ciudadano);
    }

    file.close();
    std::cout << "Tabla hash cargada desde " << archivoBinario << "\n";
}

// Función para leer un registro Ciudadano desde un archivo binario
Ciudadano leerCiudadanoDesdeBinario(const std::string& archivoBinario, uint32_t posicion) {
    std::ifstream file(archivoBinario, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo binario: " + archivoBinario);
    }

    Ciudadano ciudadano;
    // Posiciona el puntero en el lugar correcto del archivo
    file.seekg(posicion * sizeof(Ciudadano), std::ios::beg);
    // Lee el registro en la estructura Ciudadano
    file.read(reinterpret_cast<char*>(&ciudadano), sizeof(Ciudadano));

    if (file.gcount() != sizeof(Ciudadano)) {
        throw std::runtime_error("Error al leer el registro desde el archivo binario.");
    }

    return ciudadano;
}

// Cargar registros desde un archivo de índice y binarios
void CuckooHashing::cargarDesdeIndice(const std::string& archivoIndice) {
    std::ifstream indexFile(archivoIndice, std::ios::binary);
    if (!indexFile.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo de índice.");
    }

    struct Indice {
        char dni[20];
        char archivo[50];
        uint32_t posicion;
    };

    Indice entrada;
    while (indexFile.read(reinterpret_cast<char*>(&entrada), sizeof(Indice))) {
        Ciudadano ciudadano = leerCiudadanoDesdeBinario(entrada.archivo, entrada.posicion);
        insertar(ciudadano);
    }

    indexFile.close();
    std::cout << "Registros cargados desde índice.\n";
}

// Rehash
void CuckooHashing::rehash() {
    size_t newSize = tabla1.size() * 2;
    std::vector<std::optional<Ciudadano>> newTabla1(newSize);
    std::vector<std::optional<Ciudadano>> newTabla2(newSize);

    for (const auto& ciudadanoOpt : tabla1) {
        if (ciudadanoOpt.has_value()) {
            insertar(ciudadanoOpt.value());
        }
    }

    for (const auto& ciudadanoOpt : tabla2) {
        if (ciudadanoOpt.has_value()) {
            insertar(ciudadanoOpt.value());
        }
    }

    tabla1 = std::move(newTabla1);
    tabla2 = std::move(newTabla2);
    std::cout << "Rehash realizado. Nuevo tamaño: " << newSize << "\n";
}

// Para depuración
void CuckooHashing::imprimirTabla() {
    std::cout << "Tabla 1:\n";
    for (size_t i = 0; i < tabla1.size(); ++i) {
        if (tabla1[i].has_value()) {
            std::cout << "[" << i << "] " << tabla1[i]->dni << "\n";
        }
    }

    std::cout << "Tabla 2:\n";
    for (size_t i = 0; i < tabla2.size(); ++i) {
        if (tabla2[i].has_value()) {
            std::cout << "[" << i << "] " << tabla2[i]->dni << "\n";
        }
    }
}




