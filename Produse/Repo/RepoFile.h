//
// Created by Titieni Paul on 24.07.2024.
//

#ifndef PRODUSE_REPOFILE_H
#define PRODUSE_REPOFILE_H
#include "../Domain/Produs.h"
#include "../Exceptii/RepoException.h"
#include <utility>
#include <vector>
#include <fstream>

using std::vector;
using std::ifstream;
using std::ofstream;

class RepoFile {
private:
    string file_name;
    vector<Produs> produse;

    /*
     * Functia incarca in vectorul de produse, toate produsele scrise in fisier
     */
    void load_from_file();

    /*
     * Functia scrie in fisier toate produsele din vectorul de produse
     */
    void save_to_file();
public:
    /*
     * Constructorul repository ului
     * Parametrii:
     *  -file_name, reprezinta numele fisierului asupra caruia executa repository ul curent
     */
    explicit RepoFile(string file_name) : file_name{std::move(file_name)} {
        load_from_file();
    };

    /*
     * Functia adauga un produs in vector daca acesta nu exista deja
     * Parametrii:
     *  -produs, reprezinta produsul care se adauga
     * Vectorul de produse va contine si produsul curent
     */
    void adauga(const Produs& produs);

    /*
     * Functia sterge un produs,daca exista, din vectorul cu produse
     * Parametrii:
     *  -serie, reprezinta seria(id) produsului care se sterge
     * Vectorul cu produse nu va mai contine un produs cu seria data
     */
    void sterge(const string& serie);

    /*
     * Functia modifica toate campurile unui produs cu o serie data
     * Parametrii:
     *  -serie, reprezinta seria produsului care se modifica
     *  -prod, reprezinta un produs fictiv, care contine noile date
     * Produsul cu seria "serie" va avea campurile produsului prod
     */
    void modifica(const string& serie,const Produs& prod);

    /*
     * Functia cauta si returneaza un produs din lista de produse sau arunca exceptie daca nu exista
     * Parametrii:
     *  -serie, reprezinta seria produsului cautat
     */
    Produs& cauta(const string& serie);

    /*
     * Functia returneaza lista de produse
     */
    const vector<Produs>& get_all();

    vector<Produs> get_copy();
};


#endif //PRODUSE_REPOFILE_H
