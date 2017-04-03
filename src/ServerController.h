#ifndef WEB_CONTROLLER_SERVER_H
#define WEB_CONTROLLER_SERVER_H

#include <mongoose/WebController.h>

class ServerController : public Mongoose::WebController {
    private:

    public:
        ServerController();
        ~ServerController();

        // Testeando funcion basica
        void hello(Mongoose::Request &request, Mongoose::StreamResponse &response);
        
        virtual void setup();

};

#endif 
