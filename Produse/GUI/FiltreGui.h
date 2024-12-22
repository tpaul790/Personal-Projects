//
// Created by Titieni Paul on 08.08.2024.
//

#ifndef PRODUSE_FILTREGUI_H
#define PRODUSE_FILTREGUI_H
#include "../Service/Service.h"
#include "../Observer/Observer.h"
#include <QWidget>
#include <QBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>

class FiltreGui : public QWidget,public Observer{
public:
    FiltreGui(Service& serv, string tip) : service{ serv }, tip { std::move(tip) }{
        service.inscrie(this);
        init_gui();
        connect();
    };
    void set_pret(int pret);
    void set_capacitate(int capacitate);
    void set_producator(const string& prod);
private:
    Service& service;
    string tip; //tipul filtrarii
    int filtru; //1-producator,2-pret,3-capacitate
    int pret,capacitate;
    string producator;
    QVBoxLayout* main_ly = new QVBoxLayout;
    QLabel* filtru_lb = new QLabel;
    QListWidget* list = new QListWidget;
    QPushButton* inchide = new QPushButton("Close");
    void init_gui();
    void load_data();
    void connect();
    void update() override;
};


#endif //PRODUSE_FILTREGUI_H
