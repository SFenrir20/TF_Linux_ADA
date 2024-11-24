#include "crow.h"
#include "CiudadanoService.h"

int main() {
    crow::SimpleApp app;

    // Rutas API
    CROW_ROUTE(app, "/insertar").methods("POST"_method)([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) return crow::response(400, "JSON inválido");

        Ciudadano ciudadano = CiudadanoService::fromJson(body);
        if (CiudadanoService::insertar(ciudadano)) {
            return crow::response(201, "Insertado con éxito");
        }
        return crow::response(409, "DNI duplicado");
    });

    CROW_ROUTE(app, "/buscar/<string>").methods("GET"_method)([](const std::string& dni) {
        auto ciudadano = CiudadanoService::buscar(dni);
        if (ciudadano.has_value()) {
            return crow::response(crow::json::wvalue(CiudadanoService::toJson(ciudadano.value())));
        }
        return crow::response(404, "No encontrado");
    });

    // Otras rutas aquí...

    app.port(8080).multithreaded().run();
}
