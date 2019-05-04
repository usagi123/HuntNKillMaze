//
// Created by Mai Pham Quang Huy on 2019-05-04.
//

#include "Coordinator.h"

Coordinator::Coordinator() {}

Coordinator::Coordinator(int x, int y) : x(x), y(y) {}

int Coordinator::getX() const {
    return x;
}

void Coordinator::setX(int x) {
    Coordinator::x = x;
}

int Coordinator::getY() const {
    return y;
}

void Coordinator::setY(int y) {
    Coordinator::y = y;
}

Coordinator::~Coordinator() {

}
