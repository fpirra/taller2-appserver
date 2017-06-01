#ifndef APP_SERVER_SONGS_HANDLER_H
#define APP_SERVER_SONGS_HANDLER_H

#include <string>

using namespace std;

class SongsHandler{
    private:
        string server_domain = "http://ec2-54-200-74-89.us-west-2.compute.amazonaws.com/";
    public:
        SongsHandler();
        ~SongsHandler();

        bool getLink(string& song_data_file, string& song_link);
};

#endif