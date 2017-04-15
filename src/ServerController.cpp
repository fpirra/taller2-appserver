#include "ServerController.h"

using namespace std;
using namespace Mongoose;

ServerController::ServerController(Logger* logger){
    this->dbhandler = new DBhandler();
    this->validator = new Validator();
    this->logger = logger;

}

ServerController::~ServerController(){
    delete this->dbhandler;
    delete this->validator;
}

void ServerController::setup(){
    setPrefix("/appsvr"); // Agrego un prefijo, a la ruta por defecto
   
    addRouteResponse("GET", "/hellojson", ServerController, hellojson, JsonResponse);

    // Recibo por header: Authorization , y por parametro: id_song
    addRouteResponse("GET", "/song", ServerController, get_song, JsonResponse);
    
    // Recibo por header: Authorization , y por parametro: id_song, song_file
    addRouteResponse("PUT", "/song", ServerController, add_song, JsonResponse);

    // Recibo por header: Authorization , y por parametro: id_song
    addRouteResponse("DELETE", "/song", ServerController, del_song, JsonResponse);
};


void ServerController::hellojson(Mongoose::Request &request, Mongoose::JsonResponse &response){
    if ( validator->validate_token( request.getHeaderKeyValue("Authorization") ) ){

        response = response_handler.build_response(201, "Testing Json response");
        logger->log("Testing OK", Log_type::INFO);     
    
    } else {
        response = response_handler.build_response(401, "Token invalido");
        logger->log("401 - El token recibido no es valido", Log_type::WARN);
    }
   
};

void ServerController::get_song(Mongoose::Request &request, Mongoose::JsonResponse &response){
    if ( validator->validate_token( request.getHeaderKeyValue("Authorization") ) ){
        int id_song;
        try{
            id_song = stoi(request.get("id_song", ""));
        } catch(invalid_argument&) {
            response = response_handler.build_response(400, "id_song invalido");
            logger->log("400 - El id de cancion es invalido ", Log_type::ERROR);
            return ;
        }

        string song_file;

        if ( ! dbhandler->get(id_song, song_file) ){
            response = response_handler.build_response(404, "No existe la cancion solicitada");
            logger->log("404 - No existe la cancion solicitada", Log_type::ERROR);
            return ;
        };
        
        response = response_handler.build_response(201, song_file);
        logger->log("201 - Se envio la cancion: " + song_file, Log_type::INFO);
    
    } else {

        response = response_handler.build_response(401, "Token invalido");
        logger->log("401 - El token recibido no es valido", Log_type::WARN);
    }
};

void ServerController::add_song(Mongoose::Request &request, Mongoose::JsonResponse &response){
    if ( validator->validate_token( request.getHeaderKeyValue("Authorization") ) ){
        int id_song;
        try{
            id_song = stoi(request.get("id_song", ""));
        } catch(invalid_argument&) {
            response = response_handler.build_response(400, "id_song invalido");
            logger->log("400 - El id de cancion es invalido ", Log_type::ERROR);
            return ;
        }

        string song_file = request.get("song_file", "");

        if (song_file == "" ){
            response = response_handler.build_response(400, "No se recibio un cancion para cargar");
            logger->log("400 - No se recibio un cancion para cargar ", Log_type::ERROR);
            return ;
        }

        dbhandler->insert(id_song, song_file);

        response = response_handler.build_response(201, "Alta correcta");
        logger->log("201 - Se agrego la cancion: " + song_file + " a la base de datos", Log_type::INFO);

    } else {

        response = response_handler.build_response(401, "Token invalido");
        logger->log("401 - El token recibido no es valido", Log_type::WARN);

    }
};

void ServerController::del_song(Mongoose::Request &request, Mongoose::JsonResponse &response){
    if ( validator->validate_token( request.getHeaderKeyValue("Authorization") ) ){
        int id_song;
        try{
            id_song = stoi(request.get("id_song", ""));
        } catch(invalid_argument&) {
            response = response_handler.build_response(400, "id_song invalido");
            logger->log("400 - El id de cancion es invalido ", Log_type::ERROR);
            return ;
        }

        if (!dbhandler->deleteByKey(id_song)){
            response = response_handler.build_response(404, "No existe la cancion solicitada");
            logger->log("404 - No existe la cancion solicitada", Log_type::ERROR);
            return ;
        };

        response = response_handler.build_response(201, "Baja correcta");
        logger->log("201 - Se borro la cancion: " + to_string(id_song) + " de la base de datos", Log_type::INFO);

    } else {

        response = response_handler.build_response(401, "Token invalido");
        logger->log("401 - El token recibido no es valido", Log_type::WARN);

    }
};