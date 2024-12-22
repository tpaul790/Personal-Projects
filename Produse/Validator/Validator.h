//
// Created by Titieni Paul on 24.07.2024.
//

#ifndef PRODUSE_VALIDATOR_H
#define PRODUSE_VALIDATOR_H
#include <utility>
#include "../Domain/Produs.h"

class Validator {
public:
    Validator() = default;

    /*
     * Functia valideaza seria unui produs si returneaza un string cu eroarea
     */
    string validare_serie(const string& serie);

    /*
     * Functia valideaza tipul unui produs si returneaza un string cu eroarea
     */
    string validare_tip(const string& tip);

    /*
     * Functia valideaza numele unui produs si returneaza un string cu eroarea
     */
    string validare_nume(const string& nume);

    /*
     * Functia valideaza producatorul unui produs si returneaza un string cu eroarea
     */
    string validare_producator(const string& producator);

    /*
     * Functia valideaza pretul unui produs si returneaza un string cu eroarea
     */
    string validare_pret(int pret);

    /*
     * Functia valideaza capacitatea unui produs si returneaza un string cu eroarea
     */
    string validare_capacitate(int capacitate);

    ~Validator() = default;
};


#endif //PRODUSE_VALIDATOR_H
