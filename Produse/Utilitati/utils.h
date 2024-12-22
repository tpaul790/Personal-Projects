//
// Created by Titieni Paul on 27.07.2024.
//

#ifndef PRODUSE_UTILS_H
#define PRODUSE_UTILS_H
#include "../Domain/Produs.h"

bool crescator_pret(const Produs& p1, const Produs& p2);

bool descrescator_pret(const Produs& p1, const Produs& p2);

bool crescator_capacitate(const Produs& p1, const Produs& p2);

bool descrescator_capacitate(const Produs& p1, const Produs& p2);

bool crescator_producator(const Produs& p1, const Produs& p2);

bool descrescator_producator(const Produs& p1, const Produs& p2);

#endif //PRODUSE_UTILS_H
