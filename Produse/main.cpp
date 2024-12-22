#include <iostream>
#include <QApplication>
#include "Teste/teste.h"
#include "Repo/RepoFile.h"
#include "Repo/CosProduse.h"
#include "Validator/Validator.h"
#include "Service/Service.h"
#include "GUI/ProdusGui.h"

int main(int argc, char* argv[]) {
//    test_all();
    QApplication a{argc, argv};
    RepoFile repo{"data.txt"};
    CosProduse cos;
    Validator validator;
    Service service{repo,cos,validator};
    ProdusGui gui{service};
    gui.show();
    return QApplication::exec();
//    return 0;
}

