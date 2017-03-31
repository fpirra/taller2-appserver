#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <mongoose/Server.h>
#include <mongoose/WebController.h>
#include "spdlog/spdlog.h"
#include <memory>

using namespace std;
using namespace Mongoose;
namespace spd = spdlog;

class MyController : public WebController{
    public: 
        void hello(Request &request, StreamResponse &response){
          response << "Hello " << htmlEntities(request.get("name", "... what's your name ?")) << endl;
        }

        void test(Request &request, StreamResponse &response){
          response << "Testing " << htmlEntities(request.get("test", "... estamos probando como funca esto")) << endl;
        }

        void setup(){
            addRoute("GET", "/hello", MyController, hello);
            addRoute("GET", "/testing", MyController, test);
        }
};


int main(){
    int port = 8080;
    string msgToLog;
    MyController myController;
    Server server(port);
    server.registerController(&myController);

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