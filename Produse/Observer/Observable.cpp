//
// Created by Titieni Paul on 09.08.2024.
//

#include "Observable.h"

void Observable::inscrie(Observer *obs) {
    inscrisi.push_back(obs);
}

void Observable::notify() {
    for(const auto& obs : inscrisi)
        obs->update();
}

void Observable::anuleaza(Observer *obs) {
    auto it = std::find(inscrisi.begin(),inscrisi.end(),obs);
    inscrisi.erase(it);
}

