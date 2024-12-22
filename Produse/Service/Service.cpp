//
// Created by Titieni Paul on 25.07.2024.
//

#include "Service.h"

void Service::adauga(const string &serie, const string &tip, const string &nume, const string &producator, int pret,
                     int capacitate) {
    string ers;
    ers.append(validator.validare_serie(serie));
    ers.append(validator.validare_tip(tip));
    ers.append(validator.validare_nume(nume));
    ers.append(validator.validare_producator(producator));
    ers.append(validator.validare_pret(pret));
    ers.append(validator.validare_capacitate(capacitate));
    if(!ers.empty())
        throw ServiceException(ers);
    //e valid
    auto prod = Produs{serie,tip,nume,producator,pret,capacitate};
    repo.adauga(prod);
    undo.push(std::make_unique<AdaugaUndo>(repo,prod));
    notify();
}

void Service::sterge(const string &serie) {
    auto ers = validator.validare_serie(serie);
    if(!ers.empty())
        throw ServiceException(ers);
    //valid
    auto prod = repo.cauta(serie);
    undo.push(std::make_unique<StergeUndo>(repo,prod));
    repo.sterge(serie);
    vector<Produs> vect;
    for(const auto& p : cos.get_all())
        if(prod == p) {
            cos.set_total(cos.get_total()-p.get_pret());
        }else{
            vect.push_back(p);
        }
    cos.set_cos(vect);
    notify();
}

void Service::modifica(const string &serie, const string &tip, const string &nume, const string &producator, int pret,
                       int capacitate) {
    string ers;
    ers.append(validator.validare_serie(serie));
    ers.append(validator.validare_tip(tip));
    ers.append(validator.validare_nume(nume));
    ers.append(validator.validare_producator(producator));
    ers.append(validator.validare_pret(pret));
    ers.append(validator.validare_capacitate(capacitate));
    if(!ers.empty())
        throw ServiceException(ers);
    auto nou = Produs{serie,tip,nume,producator,pret,capacitate};
    auto vechi = repo.cauta(serie);
    repo.modifica(serie,nou);
    undo.push(std::make_unique<ModificaUndo>(repo,vechi,nou));
    //verific sa vad de cate ori a aparut produsul vechi in cos pentru a regla statisticile
    vector<Produs> vect;
    int cnt=0;
    for(const auto& prod : cos.get_all())
        if(prod == nou) {
            cnt++;
            vect.push_back(nou);
        }else{
            vect.push_back(prod);
        }
    auto total = cos.get_total()-cnt*vechi.get_pret()+cnt*nou.get_pret();
    cos.set_total(total);
    cos.set_cos(vect);
    notify();
}

Produs &Service::cauta(const string &serie) {
    auto ers = validator.validare_serie(serie);
    if(!ers.empty())
        throw ServiceException(ers);
    return repo.cauta(serie);
}

const vector<Produs>& Service::get_all() {
    return repo.get_all();
}

vector<Produs> Service::get_copy() {
    return repo.get_copy();
}

vector<Produs> Service::filtrare_pret(int pret) {
    vector<Produs> filtrate;
    for(const auto& produs : get_all())
        if(produs.get_pret()==pret)
            filtrate.push_back(produs);
    return filtrate;
}
vector<Produs> Service::filtrare_capacitate(int capacitate) {
    vector<Produs> filtrate;
    for(const auto& produs : get_all())
        if(produs.get_capacitate()==capacitate)
            filtrate.push_back(produs);
    return filtrate;
}

vector<Produs> Service::filtrare_producator(const std::string &producator) {
    vector<Produs> filtrate;
    for(const auto& produs : get_all())
        if(produs.get_producator()==producator)
            filtrate.push_back(produs);
    return filtrate;
}

vector<Produs> Service::sortare(std::function<bool(const Produs &, const Produs &)> cmp) {
    auto all = get_copy();
    std::sort(all.begin(),all.end(),std::move(cmp));
    return all;
}

void Service::do_undo() {
    if(undo.empty())
        throw ServiceException("Nu se poate face undo!");
    undo.top()->doUndo();
    if(undo.top()->tipActiune() == "adauga"){
        redo.push(std::make_unique<AdaugaRedo>(repo,undo.top()->getProdus()));
    }else if(undo.top()->tipActiune() == "sterge"){
        redo.push(std::make_unique<StergeRedo>(repo,undo.top()->getProdus()));
    }else{
        redo.push(std::make_unique<ModificaRedo>(repo,undo.top()->getProdus()));
    }
    undo.pop();
    notify();
}

void Service::do_redo() {
    if(redo.empty())
        throw ServiceException("Nu se poate face redo!");
    redo.top()->do_redo();
    redo.pop();
    notify();
}

void Service::adauga_cos(const std::string &serie) {
    auto ers = validator.validare_serie(serie);
    if(!ers.empty())
        throw ServiceException{ers};
    auto produs = cauta(serie);
    cos.adauga(produs);
    notify();
}

void Service::sterge_cos(const std::string &serie) {
    auto ers = validator.validare_serie(serie);
    if(!ers.empty())
        throw ServiceException{ers};
    auto produs = cauta(serie);
    cos.sterge(produs);
    notify();
}

void Service::golire_cos() {
    cos.goleste();
    notify();
}


void Service::populare_cos(int dim, const vector<Produs> &vect) {
    cos.populare(dim,repo.get_all());
    notify();
}

const vector<Produs> &Service::get_cos() {
    return cos.get_all();
}

int Service::get_total() const {
    return cos.get_total();
}
