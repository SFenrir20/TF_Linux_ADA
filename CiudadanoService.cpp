#include "CiudadanoService.h"

//Iniciar tabla hash con tamaño base
CuckooHashing CiudadanoService::hashtable(200);

bool CiudadanoService::insertar(const Ciudadano& ciudadano) {
  return hashtable.insertar(ciudadano);
}

std::optional<Ciudadano> CiudadanoService::buscar(const std::string &dni) {
  return hashtable.buscar(dni);
}

bool CiudadanoService::eliminar(const std::string &dni) {
  return hashtable.eliminar(dni);
}

json CiudadanoService::toJson(const Ciudadano &ciudadano) {
  return {
    {"dni", ciudadano.dni},
    {"nombre",ciudadano.nombres},
    {"apellidos", ciudadano.apellidos,},
    {"nacionalidad", ciudadano.nacionalidad,},
    {"lugarNacimiento", ciudadano.lugarNacimiento,},
    {"direccion",{
      {"departamento",ciudadano.direccion.departamento},
      {"provincia",ciudadano.direccion.provincia},
      {"ciudad",ciudadano.direccion.ciudad},
      {"distrito",ciudadano.direccion.distrito}
    }},
    {"telefono",ciudadano.telefono},
    {"correo",ciudadano.correo},
    {"estadoCivil",ciudadano.estadoCivil},
  };
}

Ciudadano CiudadanoService::fromJson(const json& j) {
  Direccion direccion = {
    j["direccion"]["departamento"].get<std::string>().c_str(),
     j["direccion"]["provincia"].get<std::string>().c_str(),
    j["direccion"]["ciudad"].get<std::string>().c_str(),
    j["direccion"]["distrito"].get<std::string>().c_str()

  };
  return Ciudadano(
      j["dni"]["nombre"].get<std::string>().c_str(),
      j["nombre"].get<std::string>().c_str(),
      j["apellidos"].get<std::string>().c_str(),
      j["lugarNacimiento"].get<std::string>().c_str(),
      direccion,
      j["telefono"].get<std::string>().c_str(),
      j["correo"].get<std::string>().c_str(),
      j["estadoCivil"].get<std::string>().c_str()
  );
}

