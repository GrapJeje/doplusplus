//
// Created by Jason on 15-5-2025.
//

#include <iostream>

class Line {
public:
    static void drawLine() {
        for (int i = 0; i < 80; ++i) {
            std::cout << "-";
        }
    }
};
