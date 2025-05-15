//
// Created by Jason on 15-5-2025.
//

#include "Json.h"
#include <fstream>
#include <iostream>

#include "Json.hpp"
using json = nlohmann::json;

std::string Json::getPath() {
    return "../data/tasks.json";
}

json Json::getJson() {
    std::ifstream f(getPath());
    if (!f.is_open()) {
        std::cerr << "Kan bestand Data/tasks.json niet openen!" << std::endl;
        return json{};
    }

    return json::parse(f);
}
