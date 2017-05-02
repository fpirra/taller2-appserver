#ifndef APP_SERVER_SONGS_HANDLER_H
#define APP_SERVER_SONGS_HANDLER_H

#include <string>
#include "utils/base64.h"

using namespace std;

class SongsHandler{
    private:
        string server_domain = "localhost:9900/";
    public:
        SongsHandler();
        ~SongsHandler();

        bool getLink(string& song_data_file, string& song_link);
        string encodeSong(unsigned char const* file);
};

#endif