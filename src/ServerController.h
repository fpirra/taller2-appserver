#ifndef SERVER_CONTROLLER_H
#define SERVER_CONTROLLER_H

#include <mongoose/JsonController.h>
#include "DBhandler.h"
#include "Logger.h"

class ServerController : public Mongoose::JsonController {
    
    private:
        DBhandler* dbhandler;
        Logger* logger;
    public:
        ServerController(Logger* logger);
        ~ServerController();

        // Testeando json response
        void hellojson(Mongoose::Request &request, Mongoose::JsonResponse &response);
        void get_song(Mongoose::Request &request, Mongoose::JsonResponse &response);
        void add_song(Mongoose::Request &request, Mongoose::JsonResponse &response);
        void del_song(Mongoose::Request &request, Mongoose::JsonResponse &response);

        virtual void setup();

};

#endif 
