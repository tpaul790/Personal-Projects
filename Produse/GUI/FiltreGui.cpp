//
// Created by Titieni Paul on 08.08.2024.
//

#include "FiltreGui.h"

void FiltreGui::init_gui() {
    this->setLayout(main_ly);
    auto* text_ly = new QHBoxLayout;
    auto* text = new QLabel;
    text_ly->addWidget(text);
    text_ly->addWidget(filtru_lb);
    if(tip == "producator") {
        text->setText("Produsele fabricate de: ");
        filtru = 1;
    }else if(tip == "pret"){
        text->setText("Produsele care au pretul: ");
        filtru = 2;
    }else{
        text->setText("Produsele care au capacitatea: ");
        filtru = 3;
    }
    main_ly->addLayout(text_ly);
    main_ly->addWidget(list);
    main_ly->addWidget(inchide);
}

void FiltreGui::load_data() {
    list->clear();
    vector<Produs> all;
    if(filtru == 1){
        all = service.filtrare_producator(producator);
    }else if(filtru == 2){
        all = service.filtrare_pret(pret);
    }else{
        all = service.filtrare_capacitate(capacitate);
    }
    for(const auto& produs : all){
        auto serie = produs.get_serie();
        auto nume = produs.get_nume();
        auto p_tip = produs.get_tip();
        auto price = std::to_string(produs.get_pret());
        auto prod = produs.get_producator();
        auto cap = std::to_string(produs.get_capacitate());
        string afis;
        afis.append(serie);
        afis.append(" | ");
        afis.append(p_tip);
        afis.append(" | ");
        afis.append(nume);
        afis.append(" | ");
        afis.append(prod);
        afis.append(" | ");
        afis.append(price);
        afis.append(" | ");
        afis.append(cap);
        list->addItem(QString::fromStdString(afis));
    }
}

void FiltreGui::connect() {
    QObject::connect(inchide,&QPushButton::clicked,[this](){
        this->close();
    });
}

void FiltreGui::set_pret(int p) {
    pret = p;
    filtru_lb->setText(QString::fromStdString(std::to_string(pret)));
    load_data();
}

void FiltreGui::set_capacitate(int c) {
    capacitate = c;
    filtru_lb->setText(QString::fromStdString(std::to_string(capacitate)));
    load_data();
}

void FiltreGui::set_producator(const std::string &prod) {
    producator = prod;
    filtru_lb->setText(QString::fromStdString(producator));
    load_data();
}

void FiltreGui::update() {
    load_data();
}
