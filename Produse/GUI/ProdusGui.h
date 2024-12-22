//
// Created by Titieni Paul on 25.07.2024.
//

#ifndef PRODUSE_PRODUSGUI_H
#define PRODUSE_PRODUSGUI_H
#include "../Service/Service.h"
#include "../TableModel/TableModel.h"
#include "../Utilitati/utils.h"
#include "CosGui.h"
#include "StatisticiGui.h"
#include "FiltreGui.h"
#include <QTableView>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <QSlider>
#include <QFormLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QListWidget>

class ProdusGui : public QWidget{
public:
    ProdusGui(Service& service) : service{service} {
        init_gui();
        connect();
    };
private:
    Service& service;
    QHBoxLayout* main_ly = new QHBoxLayout;
    QTableView* vw = new QTableView;
    TableModel* tabel = new TableModel{service.get_all()};
    //colectare date
    QLineEdit* serie_txt = new QLineEdit;
    QLineEdit* tip_txt = new QLineEdit;
    QLineEdit* nume_txt = new QLineEdit;
    QLineEdit* producator_txt = new QLineEdit;
    QLabel* slider_lb = new QLabel;
    QSlider* pret_txt = new QSlider{Qt::Horizontal};
    QComboBox* capacitate_txt = new QComboBox;
    //butoane simple
    QPushButton* adauga = new QPushButton{"Adauga"};
    QPushButton* sterge = new QPushButton{"Sterge"};
    QPushButton* modifica = new QPushButton{"Modifica"};
    QPushButton* undo = new QPushButton{"Undo"};
    QPushButton* redo = new QPushButton{"Redo"};
    QPushButton* cauta = new QPushButton{"Cauta"};
    QPushButton* inchide = new QPushButton{"Close"};
    //butoane mai speciale
    QPushButton* filtrare = new QPushButton{"Filtreaza"};
    QPushButton* sortare = new QPushButton{"Sorteaza"};
    QComboBox* ordine = new QComboBox;
    QComboBox* tip_sortare = new QComboBox;
    QComboBox* tip_filtrare = new QComboBox;
    //butoane cos
    QPushButton* deschide_cos = new QPushButton{"Cos"};
    QPushButton* statistici = new QPushButton{"Statistici"};
    QPushButton* adauga_cos = new QPushButton{"AdaugaCos"};
    QPushButton* sterge_cos = new QPushButton{"StergeCos"};
    QPushButton* populare = new QPushButton{"PopulareCos"};
    QComboBox* nr_populare = new QComboBox;
    QPushButton* golire = new QPushButton{"GolireCos"};

    void init_gui();
    void connect();
};


#endif //PRODUSE_PRODUSGUI_H
