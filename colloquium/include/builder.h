#include "form.h"

class FormBuilder {
public:
    virtual ~FormBuilder() {}
    virtual Form* createForm(FormType type) = 0;
};

class CircleBuilder : public FormBuilder {
public:
    Form* createForm(FormType type);
};

class SquareBuilder : public FormBuilder {
public:
    Form* createForm(FormType type);
};

class TriangleBuilder : public FormBuilder {
public:
    Form* createForm(FormType type);
};