#include <iostream>
#include <fstream> 
#include "SongsHandler.h"
#include "utils/base64.h"

using namespace std;

SongsHandler::SongsHandler(){
};

SongsHandler::~SongsHandler(){
};

string generate_random_string(const int len) {
    srand (time(NULL));
    char s[len];
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    s[len] = 0;
    return s;
}

bool SongsHandler::getLink(string& song_data_file, string& song_link){
    string file_name = generate_random_string(16);
    std::ofstream outfile ("src/songs/" + file_name + ".mp3" );
    outfile << song_data_file;
    outfile.close();

    song_link = server_domain + file_name + ".mp3";
    return true;
};

string SongsHandler::encodeSong(unsigned char const* file){
    return base64_encode(file, sizeof(file));
}



