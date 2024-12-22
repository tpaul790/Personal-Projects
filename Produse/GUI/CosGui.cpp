//
// Created by Titieni Paul on 09.08.2024.
//

#include "CosGui.h"

void CosGui::init_gui() {
    this->setLayout(main_ly);
    auto* left = new QVBoxLayout;
    auto* right = new QVBoxLayout;
    vw->setModel(tabel);
    left->addWidget(vw);
    left->addWidget(inchide);

    right->addWidget(serie_txt);
    right->addWidget(adauga);
    right->addWidget(sterge);
    right->addWidget(populare);
    right->addWidget(nr_populare);
    for(int i=1;i<=10;i++)
        nr_populare->addItem(QString::fromStdString(std::to_string(i)));
    right->addWidget(golire);

    main_ly->addLayout(left);
    main_ly->addLayout(right);
}

void CosGui::connect() {
    QObject::connect(inchide,&QPushButton::clicked,[this](){
       this->close();
    });

    QObject::connect(adauga,&QPushButton::clicked,[this](){
        if(serie_txt->text().isEmpty()){
            QMessageBox::warning(this,"Error","Va rog sa completati, in text-field, seria produsului pe  care doriti sa-l adaugati");
        }
        else{
            try {
                service.adauga_cos(serie_txt->text().toStdString());
            }catch (ServiceException& e){
                QMessageBox::warning(this,"Error",QString::fromStdString(e.get_mesaj()));
            }
            catch (RepoException& e){
                QMessageBox::warning(this,"Error",QString::fromStdString(e.get_mesaj()));
            }
        }
    });

    QObject::connect(sterge,&QPushButton::clicked,[this](){
        if(serie_txt->text().isEmpty()){
            QMessageBox::warning(this,"Error","Va rog sa completati, in text-field, seria produsului pe  care doriti sa-l adaugati");
        }
        else{
            try {
                service.sterge_cos(serie_txt->text().toStdString());
            }catch (ServiceException& e){
                QMessageBox::warning(this,"Error",QString::fromStdString(e.get_mesaj()));
            }
            catch (RepoException& e){
                QMessageBox::warning(this,"Error",QString::fromStdString(e.get_mesaj()));
            }
        }
    });

    QObject::connect(golire,&QPushButton::clicked,[this](){
       service.golire_cos();
    });

    QObject::connect(populare,&QPushButton::clicked,[this](){
       service.populare_cos(nr_populare->currentText().toInt(),service.get_all());
    });
}

void CosGui::update() {
    tabel->setProduse(service.get_cos());
}