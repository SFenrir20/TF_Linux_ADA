//
// Created by fenrirdev on 13/11/24.
//

#include "CuckooHashing.h"
#include <fstream>
#include <sstream>

// Constructor con tamaño de tablas y límite de intentos para evitar ciclos
CuckooHashing::CuckooHashing(size_t size) : tabla1(size), tabla2(size), maxIntentos(10), maxTamano(33000000) {
    if (size > maxTamano) {
        throw std::invalid_argument("El tamaño inicial excede el máximo permitido.");
    }
    std::ifstream archivo("D:\\Repos\\TF_Linux_EDA\\Generador\\ciudadanos.csv");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir archivo" << std::endl;
        throw std::runtime_error("No se pudo abrir el archivo.");
    }

    // Limita el número de líneas leídas, si es necesario
    size_t max_lineas = 1000000;
    size_t lineas_leidas = 0;

    std::string linea;
    while (std::getline(archivo, linea)&& lineas_leidas < max_lineas) {

        std::cout << lineas_leidas++ << std::endl;

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
    std::hash<std::string> hash_fn;
    return hash_fn(dni) % tabla1.size();
}

size_t CuckooHashing::hash2(const std::string& dni) {
    std::hash<std::string> hash_fn;
    return (hash_fn(dni) / tabla1.size()) % tabla2.size();
}

// Insertar un ciudadano con cuckoo hashing
bool CuckooHashing::insertar(const Ciudadano& ciudadano) {

    Ciudadano current = ciudadano;

    std::cout << "Intentando insertar ciudadano con DNI: " << current.dni << std::endl;

    for (size_t intentos = 0; intentos < maxIntentos; ++intentos) {
        size_t pos1 = hash1(current.dni);
        if (!tabla1[pos1].has_value()) {
            tabla1[pos1] = current;
            return true;
        }
        // Colisión en tabla1, reubicando
        std::cout << "Colisión en tabla1 en posición " << pos1 << ", reubicando..." << std::endl;
        // Intercambio con tabla1
        std::swap(current, tabla1[pos1].value());

        size_t pos2 = hash2(current.dni);

        if (!tabla2[pos2].has_value()) {
            tabla2[pos2] = current;
            return true;
        }

        // Colisión en tabla2, reubicando
        std::cout << "Colisión en tabla2 en posición " << pos2 << ", reubicando..." << std::endl;
        // Intercambio con tabla2
        std::swap(current, tabla2[pos2].value());
    }
    //rehash();
    // Si no se pudo insertar
    std::cerr << "Error: Ciclo detectado al intentar insertar el ciudadano con DNI: " << current.dni << std::endl;
    redimensionar();
    std::cerr << "tamaño nevo de tabla" << tabla1.size() << std::endl;
    return insertar(current);


}

void CuckooHashing::guardarDatos() {
    std::ofstream archivo("D:\\Repos\\TF_Linux_EDA\\Generador\\ciudadanos.csv");
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


void CuckooHashing::redimensionar() {
    size_t nuevoTamano = tabla1.size() * 2; // Doblar el tamaño de las tablas
    std::vector<std::optional<Ciudadano>> Tabla1_Old = tabla1;
    std::vector<std::optional<Ciudadano>> Tabla2_Old = tabla2;
    tabla1.clear();
    tabla2.clear();
    tabla1.resize(tabla1.size() * 2);
    tabla2.resize(tabla2.size() * 2);
    // Verificar que no exceda el tamaño máximo permitido
    if (nuevoTamano > maxTamano) {
        throw std::overflow_error("Error: Tamaño máximo de las tablas excedido.");
    }

    for (const auto& entry : Tabla1_Old) {
        if (entry.has_value()) {
            // Reinsertar en las nuevas tablas
            insertar(entry.value());
        }
    }
    for (const auto& entry : Tabla2_Old) {
        if (entry.has_value()) {
            // Reinsertar en las nuevas tablas
            insertar(entry.value());
        }
    }
}

bool CuckooHashing::tablaLlena() const {
    size_t elementosOcupados = 0;

    // Contar elementos ocupados en tabla1
    for (const auto& entry : tabla1) {
        if (entry.has_value()) {
            elementosOcupados++;
        }
    }

    // Contar elementos ocupados en tabla2
    for (const auto& entry : tabla2) {
        if (entry.has_value()) {
            elementosOcupados++;
        }
    }

    // Factor de carga máximo permitido (ajusta según tus necesidades)
    const double maxFactorCarga = 1;
    size_t capacidadTotal = tabla1.size() + tabla2.size();

    // Verificar si excedemos el factor de carga permitido
    return static_cast<double>(elementosOcupados) / capacidadTotal > maxFactorCarga;
}
