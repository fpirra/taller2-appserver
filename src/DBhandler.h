#ifndef DB_HANDLER_SERVER_H
#define DB_HANDLER_SERVER_H

using namespace std;

class DBhandler{

    private:

    public:

        DBhandler();
        ~DBhandler();

        // Para leer el valor, asociado a una clave
        string getValue(string key);

        // Escribir el valor que se quiere a la clave
        void putValue(string key, string value);

        // Borrar la clave de la base de datos
        void deleteKey(string key);

};

#endif 
