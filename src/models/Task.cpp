//
// Created by Jason on 15-5-2025.
//

#include "Task.h"
#include <fstream>
#include "utils/Line.cpp"

std::vector<Task> Task::tasks;

void Task::show() {
    Line::drawLine();
    std::cout << "Task ID: " << id << "\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Description: " << description << "\n";
    std::cout << "Status: " << status << "\n";
    std::cout << "Deadline: " << deadline << "\n";
}

void Task::list() {

}

void Task::add() {
}

void Task::remove() {
}

void Task::save(const Task &task) {
}
