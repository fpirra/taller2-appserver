#include <iostream>
#include "Validator.h"

using namespace std;

Validator::Validator(){
};

Validator::~Validator(){
};

bool Validator::validate_token(string token){
    // TODO: Cuando este listo el servicio del shared server para validar
    //       token, esto le enviara el token y consulta, de modo que el shared
    //       me diga si es valido o no.
    if (token == "token"){
        return true;    
    } else {
        return false;
    }
    
};



