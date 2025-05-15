#include <iostream>
#include <fstream>
#include "models/Task.h"
#include "utils/Json.h"
#include "utils/UI.h"

int main() {
    const json data = Json::getJson();
    if (data.empty()) return 1;

    Task::init(data);

    try {
        while (true) {
            switch (UI::chooseMenu()) {
                case 1:
                    UI::addTask();
                    break;
                case 2:
                    UI::showTasks();
                    break;
                case 3:
                    UI::showTask();
                    break;
                case 4:
                    UI::editTask();
                    break;
                case 5:
                    UI::deleteTask();
                    break;
                case 6:
                    UI::saveTasks();
                    break;
                case 7:
                    std::cout << "Exiting..." << std::endl;
                    return 0;
                default:
                    std::cout << "Invalid choice." << std::endl;
                    break;
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Fout: " << e.what() << std::endl;
    }

    return 0;
}