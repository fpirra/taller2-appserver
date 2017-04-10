#include <json/json.h>
#include <string>
#include "mongoose/RequestHandler.h"
#include "mongoose/Request.h"
#include "mongoose/Controller.h"
#include "mongoose/JsonResponse.h"
#include "Logger.h"
#include "ServerController.h"
#include "DBhandler.h"
#include "Validator.h"

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

    // Recibo por parametro: api_token , id_song
    addRouteResponse("POST", "/song", ServerController, get_song, JsonResponse);
    
    // Recibo por parametro: api_token , id_song, song_file
    addRouteResponse("PUT", "/song", ServerController, add_song, JsonResponse);

    // Recibo por parametro: api_token , id_song
    addRouteResponse("DELETE", "/song", ServerController, del_song, JsonResponse);
};


void ServerController::hellojson(Mongoose::Request &request, Mongoose::JsonResponse &response){
    if ( validator->validate_token( request.get("api_token", "") ) ){
        response["data"] = "Testing Json response";
        logger->log("Testing OK", Log_type::INFO);     
    } else {
        response["data"] = "El token recibido no es valido";
        logger->log("El token recibido no es valido", Log_type::WARN);
    }
   
};

void ServerController::get_song(Mongoose::Request &request, Mongoose::JsonResponse &response){
    if ( validator->validate_token( request.get("api_token", "") ) ){
        int id_song = stoi(request.get("id_song", ""));
        string song_file = dbhandler->get(id_song);
        response["song_file"] = song_file;
        logger->log("Se envio la cancion: " + song_file, Log_type::INFO);
    } else {
        response["data"] = "El token recibido no es valido";
        logger->log("El token recibido no es valido", Log_type::WARN);
    }
};

void ServerController::add_song(Mongoose::Request &request, Mongoose::JsonResponse &response){
    if ( validator->validate_token( request.get("api_token", "") ) ){
        int id_song = stoi(request.get("id_song", ""));
        string song_file = request.get("song_file", "");
        dbhandler->insert(id_song, song_file);
        response["data"] = "Song added !";
        logger->log("Se agrego la cancion: " + song_file + " a la base de datos", Log_type::INFO);
    } else {
        response["data"] = "El token recibido no es valido";
        logger->log("El token recibido no es valido", Log_type::WARN);
    }
};

void ServerController::del_song(Mongoose::Request &request, Mongoose::JsonResponse &response){
    if ( validator->validate_token( request.get("api_token", "") ) ){
        int id_song = stoi(request.get("id_song", ""));
        dbhandler->deleteByKey(id_song);
        response["data"] = "Song deleted !";
        logger->log("Se borro la cancion: " + to_string(id_song) + " de la base de datos", Log_type::INFO);
    } else {
        response["data"] = "El token recibido no es valido";
        logger->log("El token recibido no es valido", Log_type::WARN);
    }
};