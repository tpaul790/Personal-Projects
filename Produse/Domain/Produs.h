//
// Created by Titieni Paul on 24.07.2024.
//

#ifndef PRODUSE_PRODUS_H
#define PRODUSE_PRODUS_H
#include <string>
#include <utility>

using std::string;

class Produs {
private:
    string serie,tip,nume,producator;
    int pret,capacitate;
public:
    /*
     * Constructorul obiectului
     * Parametrii:
     *  -serie, reprezinta seria produsului,un string care identifica in mod unic un obiect
     *  -tip, reprezinta tipul produsului
     *  -producator, reprezinta compania care produce acest produs
     *  -pret, reprezinta pretul de vanzare al produsului
     *  -capacitate, reprezinta capacitatea de memorare a produsului
     */
    Produs(string serie, string tip, string nume, string  producator, int pret, int capacitate) : serie{std::move(serie)}, tip{std::move(tip)},nume{std::move(nume)},producator{std::move(producator)},pret{pret}, capacitate{capacitate} {};

    /*
     * Functia returneaza seria produsului curent
     */
    string get_serie() const;

    /*
     * Functia returneaza tipul produsului curent
     */
    string get_tip() const;

    /*
     * Functia returneaza numele produsului curent
     */
    string get_nume() const;

    /*
     * Finctia returneaza producatorul produsului curent
     */
    string get_producator() const;

    /*
     * Functia returneaza pretul produsului curent
     */
    int get_pret() const;

    /*
     * Functia returneaza capacitatea produsului curent
     */
    int get_capacitate() const;

    /*
     * Functia modifica tipul produsului curent
     * Parametrii:
     *  -nou, reprezinta noul tip al produsului curent
     * Produsul curent va avea tipul "nou"
     */
    void set_tip(string nou);

    /*
     * Functia modifica numele produsului curent
     * Paramtetrii:
     *  -nou, reprezinta noul nume al produsului curent
     * Produsul curent va avea numele "nou"
     */
    void set_nume(string nou);

    /*
     * Functia modifica producatorul produsului curent
     * Parametrii:
     *  -nou, reprezinta noul producator al produsului curent
     * Produsul curent va avea producatorul "nou"
     */
    void set_producator(string nou);

    /*
     * Functia modifica pretul produsului curent
     * Parametrii:
     *  -nou, reprezinta noul pret al produsului curent
     * Produsul curent va avea pretul "nou"
     */
    void set_pret(int nou);

    /*
     * Functia modifica capacitatea de memorare a produsului curent
     * Parametrii:
     *  -nou, reprezinta noua capacitate a produsului curent
     * Produsul curent va avea capacitatea "nou"
     */
    void set_capacitate(int nou);

    /*
     * Functia de suprascriere a operatorului ==
     * Functia returneaza true daca doua produse au aceeasi serie, respectiv false
     * in caz contrar.
     */
    bool operator==(const Produs& ot) const;

    /*
     * Functia de suprascriere a operatorului =(atribuire)
     */
    void operator=(const Produs& ot);
};


#endif //PRODUSE_PRODUS_H
