#include <iostream>

enum FormType {
    CIRCLE,
    SQUARE,
    TRIANGLE
};

class Form {
public:
    virtual ~Form() {}
    virtual void draw() = 0;
};

class Circle : public Form {
public:
    void draw();
};

class Square : public Form {
public:
    void draw();
};

class Triangle : public Form {
public:
    void draw();
};