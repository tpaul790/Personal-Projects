//
// Created by Titieni Paul on 09.08.2024.
//

#ifndef PRODUSE_COSPRODUSE_H
#define PRODUSE_COSPRODUSE_H
#include "../Domain/Produs.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <vector>
using std::vector;

class CosProduse {
private:
    vector<Produs> cos;
    int total;
public:
    CosProduse() : total { 0 } {};

    /*
     * Functia adauga un produs dat in cos
     * Parametrii:
     *  -produs, reprezinta produsul care se adauga in cos
     * Vectroul cos va contine produsul dat ca parametru
     */
    void adauga(const Produs& produs);

    /*
     * Functia sterge din cos un produs dat
     * Parametrii:
     *  -produs, reprezinta produsul care se doreste a fi sters
     * Vectorul cos nu va mai contine produsul dat ca parametru
     */
    void sterge(const Produs& produs);

    /*
     * Functia adauga produse random in cos
     * Parametrii:
     *  -dim, reprezinta numarul de produse care vor fi adaugate
     *  -vect, reprezinta vectorul din care se vor selecta cele dim produse random
     * Vectorul "cos" va contine "dim" produse random din vectorul "vect"
     */
    void populare(int dim, vector<Produs> vect);

    /*
     * Functia de golire a cosului de cumparaturi
     * Vectorul corespunzator cosului de cumparaturi se goleste
     */
    void goleste();

    /*
     * Functia returneaza vectorul de produse care corespunde cosului de cumparaturi
     */
    const vector<Produs>& get_all();

    /*
     * Functia creaza un intreg cos de cumparaturi
     * Parametrii:
     *  -vect, reprezinta noul cos de cumparaturi
     * Vectroul care reprezinta cosul de cumparaturi va fi echivalent cu vect
     */
    void set_cos(const vector<Produs>& vect);

    /*
     * Functia returneaza pretul total al produselor din cos
     */
    int get_total() const;

    /*
     * Functia seteaza totalul cu o valoare data
     */
    void set_total(int nou);

    ~CosProduse() = default;
};


#endif //PRODUSE_COSPRODUSE_H
