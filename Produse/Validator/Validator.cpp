//
// Created by Titieni Paul on 24.07.2024.
//

#include "Validator.h"


string Validator::validare_serie(const string& serie) {
    if(serie.empty())
        return "Serie invalida! ";
    return "";
}

string Validator::validare_tip(const string& tip) {
    if(tip != "telefon" and tip != "tableta" and tip != "casti" and tip != "laptop" and tip != "televizor")
        return ("Tip invalid! ");
    return "";
}

string Validator::validare_nume(const string& nume) {
    if(nume.empty())
        return ("Nume invalid! ");
    return "";
}

string Validator::validare_producator(const string& producator) {
    if(producator != "apple" and producator != "samsung" and producator != "asus" and producator != "hp" and producator != "lenovo")
        return ("Producator invalid! ");
    return "";
}

string Validator::validare_pret(int pret) {
    if(pret<0 or pret > 99)
        return ("Pret invalid! ");
    return "";
}

string Validator::validare_capacitate(int capacitate) {
    if(capacitate != 1 and capacitate != 64 and capacitate != 128 and capacitate != 256 and capacitate != 512 and capacitate != 1024)
        return ("Capacitate invalida! ");
    return "";
}


