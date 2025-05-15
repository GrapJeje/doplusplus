//
// Created by Jason on 15-5-2025.
//

#include <iostream>
#include <limits>

#include "models/Task.h"
#include "UI.h"

#include <thread>

#include "Line.h"

void UI::sleep(int secondes) {
    std::this_thread::sleep_for(std::chrono::seconds(secondes));
}

void UI::next() {
    while (true) {
        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.clear();
        if (std::cin.get() == '\n') {
            break;
        }
    }
}


int UI::chooseMenu() {
    int choice;

    std::cout << "Wat wil je doen?" << std::endl;
    std::cout << "1. Voeg een taak toe" << std::endl;
    std::cout << "2. Laat alle taken zien" << std::endl;
    std::cout << "3. Laat 1 bepaalde taak zien" << std::endl;
    std::cout << "4. Pas een taak aan" << std::endl;
    std::cout << "5. Verwijder een taak" << std::endl;
    std::cout << "6. Opslaan" << std::endl;
    std::cout << "7. Verlaat het programma" << std::endl;

    Line::drawLine();
    std::cout << "Vul jouw keuze in:\n";

    std::cin >> choice;

    while (std::cin.fail() || choice < 1 || choice > 7) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please enter a number between 1 and 7: \n";
        std::cin >> choice;
    }

    return choice;
}

void UI::addTask() {
    sleep(2);
    Line::drawLine();
    std::cout << "Voeg een taak toe:" << std::endl;
    sleep(1);

    // Name

    std::string name;
    std::cout << "Naam van de taak: \n";
    std::cin.ignore();
    std::getline(std::cin, name);

    // Description

    std::cout << "Beschrijving van de taak: \n";
    std::string description;
    std::getline(std::cin, description);

    // Status

    std::cout << "Status van de taak (0 = open, 1 = in progress, 2 = done): \n";
    int statusNum;
    std::cin >> statusNum;
    while (std::cin.fail() || statusNum < 0 || statusNum > 2) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please enter a number between 0 and 2: \n";
        std::cin >> statusNum;
    }
    std::string status;
    switch (statusNum) {
        case 0:
            status = "open";
            break;
        case 1:
            status = "in progress";
            break;
        case 2:
            status = "done";
            break;
        default:
            std::cerr << "Invalid status." << std::endl;
            return;
    }

    // Deadline

    std::cout << "Deadline van de taak (YYYY-MM-DD): \n";
    std::string deadline;
    std::getline(std::cin, deadline);

    Task::add(Task::getNextId(), name, description, status, deadline);
    std::cout << "Taak toegevoegd!" << std::endl;
    next();
}


void UI::showTasks() {
    sleep(2);
    Line::drawLine();
    std::cout << "Alle taken:" << std::endl;
    sleep(1);
    Task::list();
    Line::drawLine();
    next();
}

void UI::showTask() {
    sleep(2);
    Line::drawLine();
    std::cout << "Laat een specifieke taak zien:" << std::endl;
    sleep(1);

    std::cout << "Vul het ID van de taak in: \n";
    int taskId;
    std::cin >> taskId;

    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ongeldig ID. Vul een nummer in: \n";
        std::cin >> taskId;
    }

    try {
        Task task = Task::get(taskId);
        task.show();
    } catch (const std::exception &e) {
        std::cerr << "Fout: " << e.what() << std::endl;
    }

    Line::drawLine();
    next();
}

void UI::editTask() {
    sleep(2);
    Line::drawLine();
    std::cout << "Pas een taak aan:" << std::endl;
    sleep(1);

    std::cout << "Vul het ID van de taak in: \n";
    int taskId;
    std::cin >> taskId;

    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ongeldig ID. Vul een nummer in: \n";
        std::cin >> taskId;
    }

    try {
        Task task = Task::get(taskId);
        task.show();

        Line::drawLine();
        std::cout << "Wat wil je aanpassen?" << std::endl;
        std::cout << "1. Naam" << std::endl;
        std::cout << "2. Beschrijving" << std::endl;
        std::cout << "3. Status" << std::endl;
        std::cout << "4. Deadline" << std::endl;
        std::cout << "Vul jouw keuze in:\n";

        int choice;
        std::cin >> choice;

        while (std::cin.fail() || choice < 1 || choice > 4) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ongeldige keuze. Vul een nummer in tussen 1 en 4: \n";
            std::cin >> choice;
        }

        std::cin.ignore();
        std::string newValue;

        switch (choice) {
            case 1: {
                std::cout << "Nieuwe naam: \n";
                std::getline(std::cin, newValue);
                task.update("name", newValue.c_str());
                break;
            }
            case 2: {
                std::cout << "Nieuwe beschrijving: \n";
                std::getline(std::cin, newValue);
                task.update("description", newValue.c_str());
                break;
            }
            case 3: {
                std::cout << "Nieuwe status (0 = open, 1 = in progress, 2 = done): \n";
                int statusNum;
                std::cin >> statusNum;

                while (std::cin.fail() || statusNum < 0 || statusNum > 2) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ongeldige keuze. Vul een nummer in tussen 0 en 2: \n";
                    std::cin >> statusNum;
                }

                std::string status;
                switch (statusNum) {
                    case 0:
                        status = "open";
                        break;
                    case 1:
                        status = "in progress";
                        break;
                    case 2:
                        status = "done";
                        break;
                    default:
                        std::cerr << "Ongeldige status." << std::endl;
                        return;
                }

                task.update("status", status.c_str());
                break;
            }
            case 4: {
                std::cout << "Nieuwe deadline (YYYY-MM-DD): \n";
                std::getline(std::cin, newValue);
                task.update("deadline", newValue.c_str());
                break;
            }
            default:
                std::cerr << "Ongeldige keuze." << std::endl;
                break;
        }

        task.save();
        std::cout << "Taak bijgewerkt!" << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Fout: " << e.what() << std::endl;
    }

    Line::drawLine();
    next();
}

void UI::deleteTask() {
    sleep(2);
    Line::drawLine();
    std::cout << "Verwijder een taak:" << std::endl;
    sleep(1);

    std::cout << "Vul het ID van de taak in: \n";
    int taskId;
    std::cin >> taskId;

    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ongeldig ID. Vul een nummer in: \n";
        std::cin >> taskId;
    }

    try {
        Task task = Task::get(taskId);
        task.show();

        std::cout << "Weet je zeker dat je deze taak wilt verwijderen? (j/n): \n";
        char confirm;
        std::cin >> confirm;

        if (confirm == 'j' || confirm == 'J') {
            task.remove();
            task.save();
            std::cout << "Taak verwijderd!" << std::endl;
        } else std::cout << "Verwijderen geannuleerd." << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Fout: " << e.what() << std::endl;
    }

    Line::drawLine();
    next();
}

void UI::saveTasks() {
    sleep(2);
    Line::drawLine();
    std::cout << "Taken opslaan..." << std::endl;
    sleep(1);

    try {
        for (const auto &task : Task::tasks) {
            Task taskCopy = task;
            taskCopy.save();
        }
        std::cout << "Alle taken zijn opgeslagen!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Fout bij het opslaan: " << e.what() << std::endl;
    }

    Line::drawLine();
    next();
}