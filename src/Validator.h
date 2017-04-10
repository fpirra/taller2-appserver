#ifndef APP_SERVER_VALIDATOR_H
#define APP_SERVER_VALIDATOR_H

#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Validator{
    private:
    public:
        Validator();
        ~Validator();

        bool validate_token(string user, string token);
};

#endif