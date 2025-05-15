//
// Created by Jason on 15-5-2025.
//

#include <fstream>
#include <iostream>

#include "json.hpp"
using json = nlohmann::json;

class Json {
public:
    static std::string getPath() {
        return "../data/tasks.json";
    }

    static json getJson() {
        std::ifstream f(getPath());
        if (!f.is_open()) {
            std::cerr << "Kan bestand Data/tasks.json niet openen!" << std::endl;
            return 1;
        }

        return json::parse(f);
    }
};
