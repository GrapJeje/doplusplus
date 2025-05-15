//
// Created by Jason on 15-5-2025.
//

#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <vector>

#include "Json.hpp"
using json = nlohmann::json;

class Task {
public:
    int id;
    std::string name;
    std::string description;
    std::string status;
    std::string deadline;

    static std::vector<Task> tasks;

    Task(const int id, const std::string &name, const std::string &description, const std::string &status, const std::string &deadline) {
        this->id = id;
        this->name = name;
        this->description = description;
        this->status = status;
        this->deadline = deadline;
    }

    static Task get(const int id) {
        for (const auto &task : tasks) {
            if (task.id == id)
                return task;
        }
        throw std::runtime_error("Task not found");
    }

    static void init(const json& data) {
        tasks.clear();

        for (const auto& item : data) {
            int id = std::stoi(item["id"].get<std::string>());
            std::string name = item["name"];
            std::string description = item["description"];
            std::string status = item["status"];
            std::string deadline = item["deadline"];

            tasks.emplace_back(id, name, description, status, deadline);
        }
    }

    static int getNextId() {
        int maxId = 0;
        for (const auto &task : tasks) {
            if (task.id > maxId) maxId = task.id;
        }
        return maxId + 1;
    }

    void show();

    static void list();

    static void add(const int &id, const std::string &name, const std::string &description, const std::string &status, const std::string &deadline);

    void remove();

    void update(const char * what, const char *what2);

    void save();
};

#endif //TASK_H
