#include "ServerController.h"
#include "mongoose/RequestHandler.h"
#include "mongoose/Request.h"
#include "mongoose/Controller.h"
#include "mongoose/StreamResponse.h"

using namespace std;
using namespace Mongoose;

ServerController::ServerController(){
}

ServerController::~ServerController(){
}

void ServerController::setup() {
    setPrefix("/appsvr"); // Agrego un prefijo, a la ruta por defecto
   
    addRoute("GET", "/hello", ServerController, hello);

}

void ServerController::hello(Request &request, StreamResponse &response) {
    response << "Hello " << htmlEntities(request.get("name", "... what's your name ?")) << endl;
}

