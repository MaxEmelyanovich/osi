#include "../include/singleton.h"

FormFactory& FormFactory::getInstance() {
    static FormFactory instance;
    return instance;
}

Form* FormFactory::createForm(FormType type) {
    return builder_->createForm(type);
}

void FormFactory::setBuilder(FormBuilder* builder) {
    builder_ = builder;
}