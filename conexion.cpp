#include <iostream>
#include "sqlite3.h"

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    // Mostrar los resultados de la consulta
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << "\t";
    }
    std::cout << std::endl;
    return 0;
}

int main() {
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    // Abrir la base de datos
    rc = sqlite3_open("mi_base_de_datos.db", &db);
    if (rc) {
        std::cerr << "No se pudo abrir la base de datos: " << std::endl;
        return 1;
    }

    // Consulta SQL
    const char* sql = "SELECT * FROM productos;";

    // Ejecutar la consulta
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error en la consulta SQL: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

    // Cerrar la base de datos
    sqlite3_close(db);

    return 0;
}