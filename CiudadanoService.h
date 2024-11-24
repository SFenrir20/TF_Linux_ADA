//
// Created by fenrirdev on 23/11/24.
//

#ifndef CIUDADANOSERVICE_H
#define CIUDADANOSERVICE_H

#include "CuckooHashing.h"
#include "Ciudadano.h"
#include "json.hpp"

using json = nlohmann::json;

class CiudadanoService {
public:
	static bool insertar(const Ciudadano& ciudadano);
	static std::optional<Ciudadano> buscar(const std::string& dni);
	static bool eliminar(const std::string& dni);
	static json toJson(const Ciudadano& ciudadano);
	static Ciudadano fromJson(const json& j);

private:
	static CuckooHashing hashtable; // tabla hash centralizada
};



#endif //CIUDADANOSERVICE_H
