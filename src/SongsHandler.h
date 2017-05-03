#ifndef APP_SERVER_SONGS_HANDLER_H
#define APP_SERVER_SONGS_HANDLER_H

#include <string>

using namespace std;

class SongsHandler{
    private:
        string server_domain = "localhost:9900/";
    public:
        SongsHandler();
        ~SongsHandler();

        bool getLink(string& song_data_file, string& song_link);
};

#endif