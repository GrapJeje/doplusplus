//
// Created by Jason on 15-5-2025.
//

#ifndef JSON_H
#define JSON_H

#include <fstream>
#include "Json.hpp"
using json = nlohmann::json;

class Json {
public:
    static std::string getPath();
    static json getJson();
};

#endif //JSON_H
