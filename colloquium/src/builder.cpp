#include "../include/builder.h"

Form* CircleBuilder::createForm(FormType type) {
    if (type == CIRCLE) {
        return new Circle();
    }
    return nullptr;
}

Form* SquareBuilder::createForm(FormType type) {
    if (type == SQUARE) {
        return new Square();
    }
    return nullptr;
}

Form* TriangleBuilder::createForm(FormType type) {
    if (type == TRIANGLE) {
        return new Triangle();
    }
    return nullptr;
}
