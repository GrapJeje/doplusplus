#include <iostream>
#include <fstream>
#include "models/Task.h"
#include "utils/Json.cpp"

int main() {
    const json data = Json::getJson();
    if (data == 1) return 1;

    Task::init(data);

    try {
        Task::list();
        Task task = Task::get(1);
        task.update("status", "doing");
        Task::list();
        task.save();
    } catch (const std::exception& e) {
        std::cerr << "Fout: " << e.what() << std::endl;
    }

    return 0;
}

