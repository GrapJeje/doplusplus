//
// Created by Jason on 15-5-2025.
//

#include "Line.h"

#include <iostream>

void Line::drawLine() {
    for (int i = 0; i < 80; ++i) {
        std::cout << "-";
    }

    std::cout << "\n";
}
