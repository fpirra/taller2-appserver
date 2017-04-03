#include <iostream>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include "DBhandler.h"

using namespace std;

DBhandler::DBhandler(){
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};

    bsoncxx::builder::stream::document document{};

    auto collection = conn["testdb"]["testcollection"];
    document << "hello" << "world";

    collection.insert_one(document.view());
    auto cursor = collection.find({});

    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
}

DBhandler::~DBhandler() {
}

void DBhandler::putValue(string key, string value){
}

string DBhandler::getValue(string key){
    return key;
}

void DBhandler::deleteKey(string key) {
}
