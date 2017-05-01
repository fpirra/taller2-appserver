#ifndef APP_SERVER_SONGS_HANDLER_H
#define APP_SERVER_SONGS_HANDLER_H

#include <string>

using namespace std;

class SongsHandler{
    private:
        string server_domain = "localhost:8080/";
    public:
        SongsHandler();
        ~SongsHandler();

        bool getLink(string base64_song, string& song_link);
};

#endif