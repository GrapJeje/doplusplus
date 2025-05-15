#ifndef UI_H
#define UI_H

class UI {
public:
    static void sleep(int secondes);
    static void next();

    static int chooseMenu();
    static void addTask();
    static void showTasks();
    static void showTask();
    static void editTask();
    static void deleteTask();
    static void saveTasks();
};

#endif //UI_H