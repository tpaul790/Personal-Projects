//
// Created by Titieni Paul on 24.07.2024.
//

#include "RepoFile.h"

void RepoFile::load_from_file() {
    ifstream fin(file_name);
    while(!fin.eof()){
        string serie,tip,nume,producator;
        int pret,capactiate;
        fin>>serie>>tip>>nume>>producator>>pret>>capactiate;
        if(fin.eof())
            break;
        produse.push_back(Produs{serie,tip,nume,producator,pret,capactiate});
    }
    fin.close();
}

void RepoFile::save_to_file() {
    ofstream fout(file_name);
    for(const auto& produs : produse){
        auto serie = produs.get_serie();
        auto tip = produs.get_tip();
        auto nume = produs.get_nume();
        auto producator = produs.get_producator();
        auto pret = produs.get_pret();
        auto capacitate = produs.get_capacitate();
        fout<<serie<<' '<<tip<<' '<<nume<<' '<<producator<<' '<<pret<<' '<<capacitate<<'\n';
    }
    fout.close();
}

void RepoFile::adauga(const Produs &produs) {
    bool exista = false;
    for(const auto& prod : produse){
        if(prod.get_serie()==produs.get_serie())
            exista=true;
        if(exista)
            break;
    }
    if(exista)
        throw RepoException("Exista deja un produs cu aceasta serie!");
    produse.push_back(produs);
    save_to_file();
}

void RepoFile::sterge(const string &serie) {
    auto produs = cauta(serie);
    //daca trece inseamna ca produsul exista
    auto pozitie = std::find(produse.begin(),produse.end(),produs);
    produse.erase(pozitie);
    save_to_file();
}

void RepoFile::modifica(const string &serie, const Produs &prod) {
    auto& produs = cauta(serie);
    //daca trece inseamna ca produsul exista
    produs.set_tip(prod.get_tip());
    produs.set_nume(prod.get_nume());
    produs.set_producator(prod.get_producator());
    produs.set_pret(prod.get_pret());
    produs.set_capacitate(prod.get_capacitate());
    save_to_file();
}

Produs& RepoFile::cauta(const string &serie) {
    for(auto& prod : produse)
        if(prod.get_serie()==serie)
            return prod;
    throw RepoException("Nu exista niciun produs cu aceasta serie!");
}

const vector<Produs> &RepoFile::get_all() {
    return produse;
}

vector<Produs> RepoFile::get_copy() {
    return produse;
}
