#ifndef SERVER_CONTROLLER_H
#define SERVER_CONTROLLER_H

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
