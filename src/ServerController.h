#ifndef SERVER_CONTROLLER_H
#define SERVER_CONTROLLER_H

#include <mongoose/JsonController.h>
#include "DBhandler.h"
#include "spdlog/spdlog.h"

class ServerController : public Mongoose::JsonController {
    
    private:
        DBhandler* dbhandler;
        std::shared_ptr<spdlog::logger> controller_log;
    public:
        ServerController();
        ~ServerController();

        // Testeando json response
        void hellojson(Mongoose::Request &request, Mongoose::JsonResponse &response);
        void get_song(Mongoose::Request &request, Mongoose::JsonResponse &response);
        void add_song(Mongoose::Request &request, Mongoose::JsonResponse &response);
        void del_song(Mongoose::Request &request, Mongoose::JsonResponse &response);

        virtual void setup();

};

#endif 
