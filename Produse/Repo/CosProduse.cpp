//
// Created by Titieni Paul on 09.08.2024.
//

#include "CosProduse.h"

void CosProduse::adauga(const Produs &produs) {
    cos.push_back(produs);
    total+=produs.get_pret();
}

void CosProduse::sterge(const Produs &produs) {
    auto it = std::find(cos.begin(),cos.end(),produs);
    cos.erase(it);
    total-=produs.get_pret();
}

void CosProduse::populare(int dim,vector<Produs> v){
    std::uniform_int_distribution<> dist(0,v.size()-1);
    while(dim) {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(v.begin(), v.end(), std::default_random_engine(seed));
        std::mt19937 mt{std::random_device{}()};
        int rndNr = dist(mt);
        this->adauga(v[rndNr]);
        dim--;
    }
}

void CosProduse::goleste() {
    cos.clear();
    total = 0;
}

const vector<Produs> &CosProduse::get_all() {
    return cos;
}

void CosProduse::set_cos(const vector<Produs> &vect) {
    cos = vect;
}

void CosProduse::set_total(int nou) {
    total = nou;
}

int CosProduse::get_total() const {
    return total;
}
