#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <mongoose/Server.h>
#include "spdlog/spdlog.h"
#include <memory>
#include "ServerController.h"

using namespace std;
using namespace Mongoose;
namespace spd = spdlog;

int main(){
    int port = 8080;
    string msgToLog;
    ServerController serverController;
    Server server(port);
    server.registerController(&serverController);

    server.start(); 

    // Testing logger
    auto serverLog = spd::stdout_color_mt("serverLog");
    serverLog->info("Server started in port: {0:d}", port );
    serverLog->error("Asi se veria un error");
    serverLog->warn("Esto seria un warning");
    spd::set_level(spd::level::debug); // Set the logger, to debug mode
    serverLog->debug("Hola, estoy mostrando un mensaje en modo debug");

    while (1) {
        sleep(10);
    }
}