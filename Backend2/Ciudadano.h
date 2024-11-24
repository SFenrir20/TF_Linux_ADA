//
// Created by fenrirdev on 13/11/24.
//

#ifndef CIUDADANO_H
#define CIUDADANO_H


#include <string>
#include <cstring>
#include <iostream>

struct Direccion {
    char departamento[50];
    char provincia[50];
    char ciudad[50];
    char distrito[50];
};

struct Ciudadano {
    char dni[20];
    char nombres[50];
    char apellidos[50];
    char nacionalidad[20];
    char lugarNacimiento[50];
    Direccion direccion;
    char telefono[15];
    char correo[50];
    char estadoCivil[15];

    // Constructor predeterminado
    Ciudadano() = default;

    // Constructor para inicializar desde strings
    Ciudadano(const std::string& dni, const std::string& nombres, const std::string& apellidos,
              const std::string& nacionalidad, const std::string& lugarNacimiento,
              const Direccion& direccion, const std::string& telefono,
              const std::string& correo, const std::string& estadoCivil) {
        setValues(dni, nombres, apellidos, nacionalidad, lugarNacimiento, direccion, telefono, correo, estadoCivil);
    }

    // Función para establecer los valores (ajusta tamaños)
    void setValues(const std::string& dni, const std::string& nombres, const std::string& apellidos,
                   const std::string& nacionalidad, const std::string& lugarNacimiento,
                   const Direccion& direccion, const std::string& telefono,
                   const std::string& correo, const std::string& estadoCivil) {
        strncpy(this->dni, dni.c_str(), sizeof(this->dni) - 1);
        strncpy(this->nombres, nombres.c_str(), sizeof(this->nombres) - 1);
        strncpy(this->apellidos, apellidos.c_str(), sizeof(this->apellidos) - 1);
        strncpy(this->nacionalidad, nacionalidad.c_str(), sizeof(this->nacionalidad) - 1);
        strncpy(this->lugarNacimiento, lugarNacimiento.c_str(), sizeof(this->lugarNacimiento) - 1);
        strncpy(this->direccion.departamento, direccion.departamento, sizeof(this->direccion.departamento) - 1);
        strncpy(this->direccion.provincia, direccion.provincia, sizeof(this->direccion.provincia) - 1);
        strncpy(this->direccion.ciudad, direccion.ciudad, sizeof(this->direccion.ciudad) - 1);
        strncpy(this->direccion.distrito, direccion.distrito, sizeof(this->direccion.distrito) - 1);
        strncpy(this->telefono, telefono.c_str(), sizeof(this->telefono) - 1);
        strncpy(this->correo, correo.c_str(), sizeof(this->correo) - 1);
        strncpy(this->estadoCivil, estadoCivil.c_str(), sizeof(this->estadoCivil) - 1);
    }
    // Para depuración (opcional)
    void print() const {
        std::cout << "DNI: " << dni << "\n"
                  << "Nombres: " << nombres << "\n"
                  << "Apellidos: " << apellidos << std::endl;
    }
};

#endif //CIUDADANO_H
