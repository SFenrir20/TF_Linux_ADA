//
// Created by fenrirdev on 13/11/24.
//

#ifndef MENU_H
#define MENU_H

#include <string>
#include "CuckooHashing.h"

// Declaraciones de funciones del menú principal
void mostrarMenu(CuckooHashing& hashTable);

// Funciones específicas del menú (opcional, para mayor modularidad)
void insertarCiudadano(CuckooHashing& hashTable);
void buscarCiudadano(CuckooHashing& hashTable);
void eliminarCiudadano(CuckooHashing& hashTable);
void guardarTabla(CuckooHashing& hashTable);
void cargarTabla(CuckooHashing& hashTable);

#endif //MENU_H
