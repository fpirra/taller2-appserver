#ifndef DB_HANDLER_SERVER_H
#define DB_HANDLER_SERVER_H

#include <mongocxx/client.hpp>

using namespace std;

class DBhandler{
    private:

    public:
        DBhandler();
        ~DBhandler();

        // Para leer el valor, asociado a una clave
        bool get(int key, string& resultado);

        // Escribir el valor que se quiere a la clave
        void insert(int key, string value);

        // Borrar la clave de la base de datos
        bool deleteByKey(int key);

        // Muestra la base de datos
        void showDB();
};

#endif