#include <iostream>
#include <fstream>
#include "models/Task.h"

int main() {
    std::ifstream f("../data/tasks.json");
    if (!f.is_open()) {
        std::cerr << "Kan bestand Data/tasks.json niet openen!" << std::endl;
        return 1;
    }

    json data = json::parse(f);

    Task::init(data);

    try {
        Task task = Task::get(1);
        task.show();
    } catch (const std::exception& e) {
        std::cerr << "Fout: " << e.what() << std::endl;
    }

    return 0;
}
