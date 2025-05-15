//
// Created by Jason on 15-5-2025.
//

#include <iostream>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

class Line {
public:
    static void drawLine() {
        int width = 80;

#ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        }
#else
        struct winsize w;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
            width = w.ws_col;
        }
#endif

        for (int i = 0; i < width; ++i) {
            std::cout << "-";
        }
        std::cout << std::endl;
    }
};
