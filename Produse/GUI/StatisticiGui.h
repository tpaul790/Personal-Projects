//
// Created by Titieni Paul on 19.08.2024.
//

#ifndef PRODUSE_STATISTICIGUI_H
#define PRODUSE_STATISTICIGUI_H

#include "../Service/Service.h"
#include "../Observer/Observer.h"
#include <QWidget>
#include <QLabel>
#include <QBoxLayout>

class StatisticiGui : public QWidget, public Observer{
public:
    StatisticiGui(Service& service) : service{ service }{
        service.inscrie(this);
        init_gui();
    }
private:
    Service& service;
    QVBoxLayout* main_ly = new QVBoxLayout;
    QLabel* total_produse_lb = new QLabel;
    QLabel* total_pret_lb = new QLabel;
    void init_gui();
    void update() override;
};


#endif //PRODUSE_STATISTICIGUI_H
