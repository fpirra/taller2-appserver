#include <iostream>
#include "SongsHandler.h"

using namespace std;

SongsHandler::SongsHandler(){
};

SongsHandler::~SongsHandler(){
};

bool SongsHandler::getLink(string base64_song, string& song_link){
    // Convertir el archivo de base64 a mp3, con un nombre random
    // con ese nombre random, se arma el link en song_link
    string nombre_archivo = "Jijiji.mp3";
    song_link = server_domain + nombre_archivo;
    return true;
};



