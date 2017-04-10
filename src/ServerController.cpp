#include <json/json.h>
#include "mongoose/RequestHandler.h"
#include "mongoose/Request.h"
#include "mongoose/Controller.h"
#include "mongoose/JsonResponse.h"
#include "spdlog/spdlog.h"
#include "ServerController.h"
#include "DBhandler.h"

using namespace std;
using namespace Mongoose;
namespace spd = spdlog;

ServerController::ServerController(){
    this->dbhandler = new DBhandler();
    controller_log = spd::stdout_color_mt("controller_log");

}

ServerController::~ServerController(){
    delete this->dbhandler;
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
    response["data"] = "Testing Json response";
};

void ServerController::get_song(Mongoose::Request &request, Mongoose::JsonResponse &response){
    int id_song = stoi(request.get("id_song", ""));
    string song_file = dbhandler->get(id_song);
    response["song_file"] = song_file;

    controller_log->info("Se envio la cancion: {0}", song_file );
};

void ServerController::add_song(Mongoose::Request &request, Mongoose::JsonResponse &response){
    int id_song = stoi(request.get("id_song", ""));
    string song_file = request.get("song_file", "");
    dbhandler->insert(id_song, song_file);

    response["data"] = "Song added !";
    controller_log->info("Se agrego la cancion: {0} a la base de datos", song_file );
};

void ServerController::del_song(Mongoose::Request &request, Mongoose::JsonResponse &response){
    int id_song = stoi(request.get("id_song", ""));
    dbhandler->deleteByKey(id_song);

    response["data"] = "Song deleted !";
    controller_log->info("Se borro la cancion: {0:d} de la base de datos", id_song );
};