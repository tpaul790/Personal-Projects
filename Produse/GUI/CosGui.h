//
// Created by Titieni Paul on 09.08.2024.
//

#ifndef PRODUSE_COSGUI_H
#define PRODUSE_COSGUI_H

#include "../Service/Service.h"
#include "../TableModel/TableModel.h"
#include "../Observer/Observer.h"
#include <QWidget>
#include <QBoxLayout>
#include <QTableView>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>

class CosGui : public QWidget, public Observer{
public:
    CosGui(Service& service) : service{ service }{
        init_gui();
        connect();
        service.inscrie(this);
    };
private:
    Service& service;
    QHBoxLayout* main_ly = new QHBoxLayout;
    QTableView* vw = new QTableView;
    TableModel* tabel = new TableModel{service.get_cos()};
    QLineEdit* serie_txt = new QLineEdit;
    QPushButton* inchide = new QPushButton{"Close"};
    QPushButton* adauga = new QPushButton{"Adauga"};
    QPushButton* sterge = new QPushButton{"Sterge"};
    QPushButton* populare = new QPushButton{"Populare"};
    QPushButton* golire = new QPushButton{"Golire"};
    QComboBox* nr_populare = new QComboBox;

    void init_gui();
    void connect();
    void update() override;
};


#endif //PRODUSE_COSGUI_H
