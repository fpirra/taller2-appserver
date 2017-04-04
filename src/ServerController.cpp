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
}

ServerController::~ServerController(){
}

void ServerController::setup() {
    setPrefix("/appsvr"); // Agrego un prefijo, a la ruta por defecto
   
    addRouteResponse("GET", "/hellojson", ServerController, hellojson, JsonResponse);



}

void ServerController::hellojson(Mongoose::Request &request, Mongoose::JsonResponse &response){
    response["data"] = "Testing Json response";
};
