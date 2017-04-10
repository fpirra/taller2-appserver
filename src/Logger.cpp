#include <iostream>
#include "Logger.h"

using namespace std;
namespace spd = spdlog;

Logger::Logger(Log_mode mode){
    this->logger = spd::stdout_color_mt("AppServer"); 
    if (mode == DBG){
        spd::set_level(spd::level::debug); // Set the logger, to debug mode
    }
};

Logger::~Logger(){
};

void Logger::log(string log_msg, Log_type type){
    switch (type) {
        case WARN:
            logger->warn(log_msg);
            break;
        case ERROR:
            logger->error(log_msg);
            break;
        case DEBUG:
            logger->debug(log_msg);
            break;
        default:
            logger->info(log_msg);
            break;

    }
};



