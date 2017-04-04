#ifndef SERVER_CONTROLLER_H
#define SERVER_CONTROLLER_H

#include <mongoose/JsonController.h>
#include "DBhandler.h"

class ServerController : public Mongoose::JsonController {
    
    private:
        DBhandler dbhandler;
    public:
        ServerController();
        ~ServerController();

        // Testeando json response
        void hellojson(Mongoose::Request &request, Mongoose::JsonResponse &response);

        virtual void setup();

};

#endif 
