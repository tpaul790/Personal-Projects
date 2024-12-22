//
// Created by Titieni Paul on 27.07.2024.
//

#include "utils.h"

bool crescator_pret(const Produs& p1, const Produs& p2){
    return p1.get_pret()<p2.get_pret();
}

bool descrescator_pret(const Produs& p1, const Produs& p2){
    return p1.get_pret()>p2.get_pret();
}

bool crescator_capacitate(const Produs& p1, const Produs& p2){
    return p1.get_capacitate()<p2.get_capacitate();
}

bool descrescator_capacitate(const Produs& p1, const Produs& p2){
    return p1.get_capacitate()>p2.get_capacitate();
}

bool crescator_producator(const Produs& p1, const Produs& p2){
    return p1.get_producator()<p2.get_producator();
}

bool descrescator_producator(const Produs& p1, const Produs& p2){
    return p1.get_producator()>p2.get_producator();
}
