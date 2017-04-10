#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <mongoose/Server.h>
#include <memory>
#include "spdlog/spdlog.h"
#include "ServerController.h"

using namespace std;
using namespace Mongoose;
namespace spd = spdlog;

int main(int argc, char* argv[]){

    int port = 8080;
    // Si se pasa un puerto por parametro se lo usa 
    if (argc > 1) port = atoi(argv[1]);

    ServerController* serverController = new ServerController();
    Server server(port);
    server.registerController(serverController);

    server.start(); 

    auto serverLog = spd::stdout_color_mt("serverLog");
    serverLog->info("(-> UnderFy <-)");    
    serverLog->info("Puerto: {0:d}", port );
    serverLog->error("Asi se veria un error");
    spd::set_level(spd::level::debug); // Set the logger, to debug mode
    serverLog->debug("Hola, estoy mostrando un mensaje en modo debug");

    // Loop server
    bool online = true;
    string keypressed;
    while (online) {
        getline(cin, keypressed);
        if (keypressed == "q") {
            serverLog->warn("Cerrando servidor, por favor aguarde...");
            online = false;
        }
        sleep(10);
    }


    server.stop();
    spd::drop_all();
    delete serverController;
    serverLog->info("El servidor se ha cerrado correctamente");
    return 1;

}