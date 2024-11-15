//
// Created by fenrirdev on 13/11/24.
//

#ifndef CIUDADANO_H
#define CIUDADANO_H


#include <string>

struct Direccion {
    std::string departamento;
    std::string provincia;
    std::string ciudad;
    std::string distrito;
};

struct Ciudadano {
    std::string dni;
    std::string nombres;
    std::string apellidos;
    std::string nacionalidad;
    std::string lugarNacimiento;
    Direccion direccion;
    std::string telefono;
    std::string correo;
    std::string estadoCivil;

    // Constructor predeterminado
    Ciudadano() = default;

    // Constructor con parámetros
    Ciudadano(const std::string& dni, const std::string& nombres, const std::string& apellidos,
              const std::string& nacionalidad, const std::string& lugarNacimiento,
              const Direccion& direccion, const std::string& telefono,
              const std::string& correo, const std::string& estadoCivil)
        : dni(dni), nombres(nombres), apellidos(apellidos), nacionalidad(nacionalidad),
          lugarNacimiento(lugarNacimiento), direccion(direccion), telefono(telefono),
          correo(correo), estadoCivil(estadoCivil) {}
};

#endif //CIUDADANO_H
