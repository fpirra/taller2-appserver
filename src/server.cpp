#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <mongoose/Server.h>
#include <memory>
#include <string>
#include "Logger.h"
#include "ServerController.h"

using namespace std;
using namespace Mongoose;
namespace spd = spdlog;

int main(int argc, char* argv[]){
    int port = 8080;
    if (argc > 1) port = atoi(argv[1]);

    Log_mode log_mode = NORMAL;
    if (argc > 2) {
        log_mode = DBG;
    }

    //TODO: Este comando es para ejecutar el mongod en DOCKER
    // No pude encontrar la forma de hacerlo con dockerfile
    system("mongod --dbpath /var/lib/mongodb &");

    Logger* logger = new Logger(log_mode);
    ServerController* serverController = new ServerController(logger);

    const char* carpeta_archivos = "./src/songs";
    
    Server server(port, carpeta_archivos);
    server.registerController(serverController);
    server.setOption("extra_headers","Access-Control-Allow-Origin: *");
    server.setOption("extra_headers","Access-Control-Allow-Methods: OPTIONS, GET, PUT, POST, DELETE");
    server.setOption("extra_headers","Access-Control-Allow-Headers: Authorization");
    server.setOption("extra_headers","Access-Control-Allow-Credentials: true");
    server.setOption("extra_headers","Allow: OPTIONS, GET, PUT, POST, DELETE"); 
    server.setOption("extra_mime_types", "multipart/form-data");
    server.start(); 

    logger->log("(-> UnderFy <-)", Log_type::INFO);    
    logger->log("Puerto: " + to_string(port), Log_type::INFO);

    // Loop server
    bool online = true;
    string keypressed;
    while (online) {
        getline(cin, keypressed);
        if (keypressed == "q") {
            logger->log("Cerrando servidor, por favor aguarde...", Log_type::WARN);
            online = false;
        }
        sleep(100);
    }

    server.stop();
    spd::drop_all();
    delete serverController;
    delete logger;
    logger->log("El servidor se ha cerrado correctamente", Log_type::INFO);
    return 1;

}