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

TEST(Validator, ManejaTokenVacio) {
    string token = "";
    Validator* validator = new Validator();
    EXPECT_FALSE(validator->validate_token(token));
    delete validator;
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}