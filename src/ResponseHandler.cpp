#include <iostream>
#include "ResponseHandler.h"

using namespace std;

ResponseHandler::ResponseHandler(){
};

ResponseHandler::~ResponseHandler(){
};

Mongoose::JsonResponse ResponseHandler::build_response(int code, string message){
    Mongoose::JsonResponse response;
    response["code"] = code;
    response["message"] = message;    
    return response;
};



