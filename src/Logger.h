#ifndef APP_SERVER_LOGGER_H
#define APP_SERVER_LOGGER_H

#include <iostream>
#include <memory>
#include <string>
#include <spdlog/spdlog.h>

using namespace std;
namespace spd = spdlog;

enum Log_mode {NORMAL, DBG};

enum Log_type {INFO, WARN, ERROR, DEBUG};

class Logger{
    private:
        shared_ptr<spdlog::logger> logger;
    public:
        Logger(Log_mode mode);
        ~Logger();

        void log(string log_msg, Log_type type);

};

#endif