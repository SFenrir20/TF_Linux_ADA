//
// Created by fenrirdev on 13/11/24.
//

#ifndef CUCKOOHASHING_H
#define CUCKOOHASHING_H

#include <vector>
#include <string>
#include <optional>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Ciudadano.h"

class CuckooHashing {
public:
    explicit CuckooHashing(size_t size);
    bool insertar(const Ciudadano& ciudadano);
    std::optional<Ciudadano> buscar(const std::string& dni);
    bool eliminar(const std::string& dni);
    void guardarTabla(const std::string& archivoBinario);
    void cargarTablaDesdeBinario(const std::string& archivoBinario);
    void cargarDesdeIndice(const std::string& archivoIndice);
    void imprimirTabla(); // Para depuración

private:
    std::vector<std::optional<Ciudadano>> tabla1;
    std::vector<std::optional<Ciudadano>> tabla2;
    size_t maxIntentos;

    size_t hash1(const std::string& dni) const;
    size_t hash2(const std::string& dni) const;
    void rehash();



};



#endif //CUCKOOHASHING_H
