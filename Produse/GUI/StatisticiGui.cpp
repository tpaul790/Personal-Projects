//
// Created by Titieni Paul on 19.08.2024.
//

#include "StatisticiGui.h"

void StatisticiGui::init_gui() {
    this->setLayout(main_ly);
    auto* text1 = new QLabel{"Numarul total de produse din cos: "};
    auto* total_produse_ly = new QHBoxLayout;
    total_produse_ly->addWidget(text1);
    total_produse_lb->setText(QString::fromStdString(std::to_string(service.get_cos().size())));
    total_produse_ly->addWidget(total_produse_lb);

    auto* text2 = new QLabel{"Pretul total al produselor din cos: "};
    auto* total_pret_ly = new QHBoxLayout;
    total_pret_ly->addWidget(text2);
    total_pret_lb->setText(QString::fromStdString(std::to_string(service.get_total())));
    total_pret_ly->addWidget(total_pret_lb);
    main_ly->addLayout(total_produse_ly);
    main_ly->addLayout(total_pret_ly);
}

void StatisticiGui::update() {
    total_produse_lb->setText(QString::fromStdString(std::to_string(service.get_cos().size())));
    total_pret_lb->setText(QString::fromStdString(std::to_string(service.get_total())));
}