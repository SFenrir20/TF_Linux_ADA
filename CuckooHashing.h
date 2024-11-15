//
// Created by fenrirdev on 13/11/24.
//

#ifndef CUCKOOHASHING_H
#define CUCKOOHASHING_H

#include <vector>
#include <string>
#include <optional>
#include <iostream>
#include "Ciudadano.h"

class CuckooHashing {
public:
    CuckooHashing(size_t size);
    bool insertar(const Ciudadano& ciudadano);
    void guardarDatos();
    std::optional<Ciudadano> buscar(const std::string& dni);
    bool eliminar(const std::string& dni);

private:
    std::vector<std::optional<Ciudadano>> tabla1;
    std::vector<std::optional<Ciudadano>> tabla2;
    size_t maxIntentos;  // Para evitar ciclos infinitos en cuckoo hashing
    size_t hash1(const std::string& dni);
    size_t hash2(const std::string& dni);
    void rehash();
};


#endif //CUCKOOHASHING_H
