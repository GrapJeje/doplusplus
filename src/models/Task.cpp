//
// Created by Jason on 15-5-2025.
//

#include "Task.h"
#include <fstream>
#include "utils/Line.h"
#include "utils/Json.h"
#include <cstring>

std::vector<Task> Task::tasks;

void Task::show() {
    Line::drawLine();
    std::cout << "Taak ID: " << id << "\n";
    std::cout << "Naam: " << name << "\n";
    std::cout << "Beschrijving: " << description << "\n";
    std::cout << "Status: " << status << "\n";
    std::cout << "Deadline: " << deadline << "\n";
}

void Task::list() {
    Line::drawLine();
    for (const auto &task: tasks) {
        std::cout << "Taak ID: " << task.id << ", Taak: " << task.name << "\n";
    }
}

void Task::add(const int &id, const std::string &name, const std::string &description, const std::string &status, const std::string &deadline) {
    tasks.emplace_back(id, name, description, status, deadline);
}

void Task::remove() {
    std::erase_if(tasks,
                  [this](const Task &t) {
                      return t.id == this->id;
                  }
    );
}

void Task::update(const char* what, const char* what2) {
    if (strcmp(what, "name") == 0) this->name = what2;
    else if (strcmp(what, "description") == 0) this->description = what2;
    else if (strcmp(what, "status") == 0) this->status = what2;
    else if (strcmp(what, "deadline") == 0) this->deadline = what2;
    else {
        std::cerr << "Onbekend veld: " << what << std::endl;
        return;
    }

    for (auto& task : tasks) {
        if (task.id == this->id) {
            if (strcmp(what, "name") == 0) task.name = what2;
            else if (strcmp(what, "description") == 0) task.description = what2;
            else if (strcmp(what, "status") == 0) task.status = what2;
            else if (strcmp(what, "deadline") == 0) task.deadline = what2;
            break;
        }
    }
}

void Task::save() {
    json data = Json::getJson();

    bool existsInTasks = false;
    for (const auto& task : tasks) {
        if (task.id == this->id) {
            existsInTasks = true;
            break;
        }
    }

    if (!existsInTasks) {
        data.erase(std::remove_if(data.begin(), data.end(),
            [this](const json& item) {
                return item["id"] == std::to_string(this->id);
            }), data.end()
        );
    } else {
        bool updated = false;
        for (auto& item : data) {
            if (item["id"] == std::to_string(this->id)) {
                item["name"] = this->name;
                item["description"] = this->description;
                item["status"] = this->status;
                item["deadline"] = this->deadline;
                updated = true;
                break;
            }
        }
        if (!updated) {
            data.push_back({
                {"id", std::to_string(this->id)},
                {"name", this->name},
                {"description", this->description},
                {"status", this->status},
                {"deadline", this->deadline}
            });
        }
    }

    std::ofstream outFile(Json::getPath());
    if (!outFile.is_open()) {
        std::cerr << "Kan tasks.json niet openen voor schrijven!" << std::endl;
        return;
    }

    outFile << data.dump(4);
    outFile.close();
}

