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
        string get(int key);

        // Escribir el valor que se quiere a la clave
        void insert(int key, string value);

        // Borrar la clave de la base de datos
        void deleteByKey(int key);

        void showDB();
};

#endif