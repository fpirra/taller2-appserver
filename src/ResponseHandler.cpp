#include <iostream>
#include "ResponseHandler.h"

using namespace std;

ResponseHandler::ResponseHandler(){
};

ResponseHandler::~ResponseHandler(){
};

Mongoose::JsonResponse ResponseHandler::build_response(int code, string message){
    Mongoose::JsonResponse response;
    response.setHeader("Access-Control-Allow-Origin", "*");
    response.setHeader("Access-Control-Allow-Methods", "OPTIONS, GET, PUT, POST, DELETE");
    response.setHeader("Access-Control-Allow-Headers", "Authorization");
    response.setHeader("Allow", "OPTIONS, GET, PUT, POST, DELETE"); 
    response["code"] = code;
    response["message"] = message;    
    return response;
};



