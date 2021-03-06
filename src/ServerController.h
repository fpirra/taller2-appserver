#ifndef SERVER_CONTROLLER_H
#define SERVER_CONTROLLER_H

#include <mongoose/JsonController.h>
#include <json/json.h>
#include <string>
#include "mongoose/RequestHandler.h"
#include "mongoose/Request.h"
#include "mongoose/Controller.h"
#include "DBhandler.h"
#include "Logger.h"
#include "Validator.h"
#include "ResponseHandler.h"
#include "SongsHandler.h"

class ServerController : public Mongoose::JsonController {
    
    private:
        DBhandler* dbhandler;
        Logger* logger;
        Validator* validator;
        SongsHandler songsHandler;
        ResponseHandler response_handler;

    public:
        ServerController(Logger* logger);
        ~ServerController();

        // Testeando json response
        void test(Mongoose::Request &request, Mongoose::JsonResponse &response);
        void opt(Mongoose::Request &request, Mongoose::JsonResponse &response);
        void get_song(Mongoose::Request &request, Mongoose::JsonResponse &response);
        void add_song(Mongoose::Request &request, Mongoose::JsonResponse &response);
        void del_song(Mongoose::Request &request, Mongoose::JsonResponse &response);

        virtual void setup();

};

#endif 
