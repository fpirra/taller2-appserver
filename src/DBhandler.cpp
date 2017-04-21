#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/types.hpp>
#include <bsoncxx/exception/exception.hpp>
#include "DBhandler.h"

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

using namespace std;

DBhandler::DBhandler(){
    mongocxx::instance instance{}; 
};

DBhandler::~DBhandler(){
};

void DBhandler::insert(int key, string value){
    mongocxx::client client{mongocxx::uri{"mongodb://localhost:27017"}};
    mongocxx::database dbUnderfy = client["UnderfyAppSvrDB"]; // Se accede o crea (si existe), la base de datos underfyAppSvrDB
    mongocxx::collection tSongs = dbUnderfy["Songs"]; // Las colecciones, son como las tablas. Creamos la "tabla" canciones

    // Creo un documento, en formato json, para insertar
    bsoncxx::builder::stream::document document{};

    document << "id_song" << key;
    document << "song_file" << value;
    tSongs.insert_one(document.view());
};

bool DBhandler::get(int key, string& resultado){
    mongocxx::client client{mongocxx::uri{"mongodb://localhost:27017"}};
    mongocxx::database dbUnderfy = client["UnderfyAppSvrDB"]; // Se accede o crea (si existe), la base de datos underfyAppSvrDB
    mongocxx::collection tSongs = dbUnderfy["Songs"]; // Las colecciones, son como las tablas. Creamos la "tabla" canciones

    mongocxx::stdx::optional<bsoncxx::document::value> result =
         tSongs.find_one(document{} << "id_song" << key << finalize);
    bsoncxx::document::view resultView = result->view(); // Como son de solo lectura los archivos bsoncxx, utilizo el view, que me devuelve
                                                        // un bsoncxx::document::element , luego lo proceso para sacar el string. 
    try {
        resultado = resultView["song_file"].get_utf8().value.to_string();
    } catch (bsoncxx::exception& e){
        return false;    
    }

    return true;
};

bool DBhandler::deleteByKey(int key) {
    mongocxx::client client{mongocxx::uri{"mongodb://localhost:27017"}};
    mongocxx::database dbUnderfy = client["UnderfyAppSvrDB"]; // Se accede o crea (si existe), la base de datos underfyAppSvrDB
    mongocxx::collection tSongs = dbUnderfy["Songs"]; // Las colecciones, son como las tablas. Creamos la "tabla" canciones

    tSongs.delete_one(document{} << "id_song" << key << finalize) ;
    
    string filesong;
    
    if ( this->get(key, filesong) ){
        return false;
    }

    return true; 
};

void DBhandler::showDB(){
    mongocxx::client client{mongocxx::uri{"mongodb://localhost:27017"}};
    mongocxx::database dbUnderfy = client["UnderfyAppSvrDB"]; // Se accede o crea (si existe), la base de datos underfyAppSvrDB
    mongocxx::collection tSongs = dbUnderfy["Songs"]; // Las colecciones, son como las tablas. Creamos la "tabla" canciones
 
    auto cursor = tSongs.find({});

    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
};


