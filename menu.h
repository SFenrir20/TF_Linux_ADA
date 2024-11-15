//
// Created by fenrirdev on 13/11/24.
//

#ifndef MENU_H
#define MENU_H


#include <string>
#include "CuckooHashing.h"

void cargarDatosDesdeCSV(const std::string& nombreArchivo, CuckooHashing& tablaHash);
void mostrarMenu(CuckooHashing& hashTable);



#endif //MENU_H
