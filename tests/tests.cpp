#include <iostream>
#include <gtest/gtest.h>
#include <mongoose/Server.h>
#include <string>
#include "DBhandler.h"
#include "Logger.h"
#include "ResponseHandler.h"
#include "ServerController.h"
#include "Validator.h"

using namespace std;

// Para generar tests, se utiliza la siguiente estructura:
//
//  TEST(MetodoParaTestear, NombreDelTest) {
//       ...
//       ...
//    EXPECT_EQ(valorEsperado, funcionAtestear(valoresQueRecive));
//  }

// Se puede utilizar EXPECT_TRUE, EXPECT_FALSE o EXPECT_EQ. Segun sea el caso a testear

// TEST(DBhandler, ManejaTokenInvalidoOvacio) {
//     string token = "";
//     Validator* validator = new Validator();
//     EXPECT_FALSE(validator->validate_token(token));
//     token = "kadlkjasdfl";
//     EXPECT_FALSE(validator->validate_token(token));
//     delete validator;
// }

// TEST(Logger, ManejaTokenInvalidoOvacio) {
//     string token = "";
//     Validator* validator = new Validator();
//     EXPECT_FALSE(validator->validate_token(token));
//     token = "kadlkjasdfl";
//     EXPECT_FALSE(validator->validate_token(token));
//     delete validator;
// }

TEST(ResponseHandler, RespondeCorrectamente) {
    Mongoose::JsonResponse response;
    ResponseHandler response_handler;
    string texto = "testeando respuesta";
    response = response_handler.build_response(201, texto);
    Json::Value jsonValue = response["message"];
    string textoRespuesta = jsonValue.asString();
    
    EXPECT_EQ(texto, textoRespuesta);
}

// TEST(ServerController, ManejaTokenInvalidoOvacio) {
//     string token = "";
//     Validator* validator = new Validator();
//     EXPECT_FALSE(validator->validate_token(token));
//     token = "kadlkjasdfl";
//     EXPECT_FALSE(validator->validate_token(token));
//     delete validator;
// }

TEST(Validator, ManejaTokenInvalidoOvacio) {
    string token = "";
    Validator* validator = new Validator();
    EXPECT_FALSE(validator->validate_token(token));
    token = "kadlkjasdfl";
    EXPECT_FALSE(validator->validate_token(token));
    delete validator;
}

TEST(Validator, ManejaTokenCorrecto) {
    string token = "basic token";
    Validator* validator = new Validator();
    EXPECT_TRUE(validator->validate_token(token));
    delete validator;
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}