#include <iostream>
#include <gtest/gtest.h>
#include <mongoose/Server.h>
#include <string>
#include "DBhandler.h"
#include "Logger.h"
#include "ResponseHandler.h"
#include "ServerController.h"
#include "Validator.h"
#include "SongsHandler.h"

using namespace std;
using namespace Mongoose;

// Para generar tests, se utiliza la siguiente estructura:
//
//  TEST(MetodoParaTestear, NombreDelTest) {
//       ...
//       ...
//    EXPECT_EQ(valorEsperado, funcionAtestear(valoresQueRecive));
//  }

// Se puede utilizar EXPECT_TRUE, EXPECT_FALSE o EXPECT_EQ. Segun sea el caso a testear

TEST(DBhandler, CargaCancionCorrecta) {
    DBhandler* dbhandler = new DBhandler();
    string textoRespuesta;
    if (! dbhandler->get(99999999, textoRespuesta) ){
        dbhandler->insert(99999999, "testSong");
    }
    dbhandler->get(99999999, textoRespuesta);

    EXPECT_EQ("testSong", textoRespuesta);
    delete dbhandler;
}

TEST(DBhandler, BorraCancionCorrecta) {
    DBhandler* dbhandler = new DBhandler();
    string textoRespuesta;
    if (! dbhandler->get(99999999, textoRespuesta) ){
        dbhandler->insert(99999999, "testSong");
    }
    dbhandler->deleteByKey(99999999);

    EXPECT_FALSE(dbhandler->get(99999999, textoRespuesta));
    delete dbhandler;
}

TEST(Logger, GenerarLogsCorrectamente) {
    Logger* logger = new Logger(Log_mode::DBG);
    logger->log("INFO", Log_type::INFO); 
    logger->log("WARN", Log_type::WARN); 
    logger->log("ERROR", Log_type::ERROR); 
    logger->log("DEBUG", Log_type::DEBUG); 
    delete logger;
}

TEST(ResponseHandler, RespondeCorrectamente) {
    Mongoose::JsonResponse response;
    ResponseHandler response_handler;
    string texto = "testeando respuesta";
    response = response_handler.build_response(201, texto);
    Json::Value jsonValue = response["message"];
    string textoRespuesta = jsonValue.asString();
    
    EXPECT_EQ(texto, textoRespuesta);
}

TEST(SongsHandler, GeneraLinkYarchivo) {
    SongsHandler songsHandler;
    string song_link;
    string data = "somerandomstring";
    EXPECT_TRUE(songsHandler.getLink(data, song_link));
}

// TEST(ServerController, ObtenerCancionOk) {
//     Mongoose::JsonResponse response;
//     Mongoose::Request request;
//     Logger* logger = new Logger(Log_mode::DBG);
//     ServerController* serverController = new ServerController(logger);

//     serverController->get_song(request, response);

//     delete serverController;
//     delete logger;
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