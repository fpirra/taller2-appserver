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
   
    addRouteResponse("GET", "/test", ServerController, test, JsonResponse);

    // Se agrega esto por el problema de cross domain
    addRouteResponse("OPTIONS", "/song", ServerController, opt, JsonResponse);

    // Recibo por HEADER: Authorization , y por PARAMETRO: id_song
    addRouteResponse("GET", "/song", ServerController, get_song, JsonResponse);
    
    // Recibo por HEADER: Authorization , por PARAMETRO: id_song y por BODY: song_file
    addRouteResponse("PUT", "/song", ServerController, add_song, JsonResponse);

    // Recibo por HEADER: Authorization , y por PARAMETRO: id_song
    addRouteResponse("DELETE", "/song", ServerController, del_song, JsonResponse);
};


void ServerController::test(Mongoose::Request &request, Mongoose::JsonResponse &response){
    if ( validator->validate_token( request.getHeaderKeyValue("Authorization") ) ){
        // Descomentar para que muestre la base de datos por consola
        // dbhandler->showDB();
        response = response_handler.build_response(201, "Monstrando base de datos");
        logger->log("Testing OK", Log_type::INFO);     
    
    } else {
        response = response_handler.build_response(401, "Token invalido");
        logger->log("401 - El token recibido no es valido", Log_type::WARN);
    }
   
};


void ServerController::opt(Mongoose::Request &request, Mongoose::JsonResponse &response){
        response = response_handler.build_response(201, "Options");
        logger->log("Sending options", Log_type::INFO);     

};

void ServerController::get_song(Mongoose::Request &request, Mongoose::JsonResponse &response){
    //Cada vez que se pide una nueva cancion, se eliminan todas las antiguas, +15 mins...
    system("find ./src/songs/* -mmin +15 -exec rm -f {} \\;");

    if ( validator->validate_token( request.getHeaderKeyValue("Authorization") ) ){
        int id_song;
        try{
            id_song = stoi(request.get("id_song", ""));
        } catch(invalid_argument&) {
            response = response_handler.build_response(400, "id_song invalido");
            logger->log("400 - El id de cancion es invalido ", Log_type::ERROR);
            return ;
        }

        string song_data_file;

        if ( ! dbhandler->get(id_song, song_data_file) ){
            response = response_handler.build_response(404, "No existe la cancion solicitada");
            logger->log("404 - No existe la cancion solicitada", Log_type::ERROR);
            return ;
        };

        string song_link;
        songsHandler.getLink(song_data_file, song_link);

        response = response_handler.build_response(201, song_link);
        logger->log("201 - Se envio la cancion: " + to_string(id_song), Log_type::INFO);
    
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

        request.handleUploads();
        vector<UploadFile>::iterator it = request.uploadFiles.begin();
        int cantCargadas = 0;
        for (; it != request.uploadFiles.end(); it++) {
            UploadFile file = *it;
            dbhandler->insert(id_song, file.getData());
            cantCargadas++;
        }  

        if (cantCargadas < 1 ){
            response = response_handler.build_response(400, "No se recibio un cancion para cargar");
            logger->log("400 - No se recibio un cancion para cargar ", Log_type::ERROR);
            return ;
        }

        response = response_handler.build_response(201, "Alta correcta");
        logger->log("201 - Se agrego/modifico la cancion: " + to_string(id_song), Log_type::INFO);

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

        if ( ! dbhandler->deleteByKey(id_song) ){
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