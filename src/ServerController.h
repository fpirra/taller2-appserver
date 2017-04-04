#ifndef SERVER_CONTROLLER_H
#define SERVER_CONTROLLER_H

#include <mongoose/JsonController.h>

class ServerController : public Mongoose::JsonController {
    
    private:

    public:
        ServerController();
        ~ServerController();

        // Testeando json response
        void hellojson(Mongoose::Request &request, Mongoose::JsonResponse &response);

        virtual void setup();

};

#endif 
