//
// Created by Titieni Paul on 24.07.2024.
//

#include "Produs.h"
#include <utility>

string Produs::get_serie() const {
    return serie;
}

string Produs::get_tip() const {
    return tip;
}

string Produs::get_nume() const {
    return nume;
}

string Produs::get_producator() const {
    return producator;
}

int Produs::get_pret() const {
    return pret;
}

int Produs::get_capacitate() const {
    return capacitate;
}

void Produs::set_tip(string nou) {
    this->tip=std::move(nou);
}

void Produs::set_nume(string nou) {
    this->nume=std::move(nou);
}

void Produs::set_producator(string nou) {
    this->producator=std::move(nou);
}

void Produs::set_pret(int nou) {
    this->pret=nou;
}

void Produs::set_capacitate(int nou) {
    this->capacitate=nou;
}

bool Produs::operator==(const Produs &ot) const{
    return this->serie==ot.get_serie();
}

void Produs::operator=(const Produs &ot) {
    this->serie = ot.serie;
    this->nume = ot.nume;
    this->tip = ot.tip;
    this->capacitate = ot.capacitate;
    this->pret = ot.pret;
    this->producator = ot.producator;
}


