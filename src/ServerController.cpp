#include "ServerController.h"
#include "mongoose/RequestHandler.h"
#include "mongoose/Request.h"
#include "mongoose/Controller.h"
#include "mongoose/JsonResponse.h"
#include <json/json.h>
#include "DBhandler.h"

using namespace std;
using namespace Mongoose;

ServerController::ServerController(){
    this->dbhandler = new DBhandler();
}

ServerController::~ServerController(){
}

void ServerController::setup() {
    setPrefix("/appsvr"); // Agrego un prefijo, a la ruta por defecto
   
    addRouteResponse("GET", "/hellojson", ServerController, hellojson, JsonResponse);

    // Recibo por parametro: api_token , id_song
    addRouteResponse("GET", "/song", ServerController, song, JsonResponse);
    
    addRouteResponse("GET", "/add_song", ServerController, add_song, JsonResponse);

    addRouteResponse("GET", "/del_song", ServerController, del_song, JsonResponse);
};

void ServerController::hellojson(Mongoose::Request &request, Mongoose::JsonResponse &response){
    response["data"] = "Testing Json response";
};

void ServerController::song(Mongoose::Request &request, Mongoose::JsonResponse &response){
    dbhandler->get( stoi(request.get("key", "")) );
    response["data"] = "OK";
};

void ServerController::add_song(Mongoose::Request &request, Mongoose::JsonResponse &response){
    dbhandler->insert( stoi(request.get("key", "")) , request.get("song", "") );
    response["data"] = "OK";
};

void ServerController::del_song(Mongoose::Request &request, Mongoose::JsonResponse &response){
    dbhandler->deleteByKey( stoi(request.get("key", "")) );
    response["data"] = "OK";
};