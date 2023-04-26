#include "form.h"
#include "builder.h"

class FormFactory {
public:
    static FormFactory& getInstance();

    Form* createForm(FormType type);

    void setBuilder(FormBuilder* builder);

private:
    FormFactory() {}
    FormBuilder* builder_;
};