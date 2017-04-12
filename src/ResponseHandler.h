#ifndef APP_SERVER_RESPONSE_HANDLER_H
#define APP_SERVER_RESPONSE_HANDLER_H

#include <string>
#include "mongoose/JsonResponse.h"

using namespace std;

class ResponseHandler{
    private:
    public:
        ResponseHandler();
        ~ResponseHandler();

        Mongoose::JsonResponse build_response(int code, string message);
};

#endif