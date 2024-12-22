//
// Created by Titieni Paul on 25.07.2024.
//

#ifndef PRODUSE_SERVICE_H
#define PRODUSE_SERVICE_H

#include "../Exceptii/ServiceException.h"
#include "../Domain/Produs.h"
#include "../Repo/RepoFile.h"
#include "../Repo/CosProduse.h"
#include "../Validator/Validator.h"
#include "../Abstract/ActiuneUndo.h"
#include "../Abstract/ActiuneRedo.h"
#include "../Observer/Observable.h"
#include <functional>
#include <stack>

using std::stack;
using std::unique_ptr;

class Service : public Observable{
private:
    RepoFile& repo;
    CosProduse& cos;
    Validator& validator;
    stack<unique_ptr<ActiuneUndo>> undo;
    stack<unique_ptr<ActiuneRedo>> redo;
public:
    /*
     * Constructorul obiectului service
     * Parametrii:
     *  -repo, un obiect de tip FileRepo
     *  -validator, un obiect de tip validator
     */
    Service(RepoFile& repo, CosProduse& cos, Validator& validator) : repo{repo},cos{cos}, validator{validator} {};

    /*
     * Functia adauga un nou produs din service
     * Parametrii:
     *  -serie, seria produsului de adaugat
     *  -tip, tipul produsului de adaugat
     *  -nume, numele produsului de adaugat
     *  -producator, producatorul produsului de adaugat
     *  -pret, pretul produsului de adaugat
     *  -capacitate, capacitatea produsului de adaugat
     * Se creeaza un produs cu aceste campuri dupa validarea lor si se adauga in vector.
     */
    void adauga(const string& serie, const string& tip, const string& nume, const string& producator, int pret, int capacitate);

    /*
     * Functia sterge un produs existent
     * Parametrii:
     *  -serie, seria produsului care se doreste a fi sters
     * Produsul cu seria data nu se mai afla in vectorul de produse
     */
    void sterge(const string& serie);

    /*
     * Functia modifica datele unui produs existent
     * Parametrii:
     *  -serie, seria produsului care se modifica
     *  -tip, noul tip al produsului cu seria "serie"
     *  -nume, noul nume al produsului
     *  -producator, noul producator al produsului
     *  -pret, noul pret al produsului
     *  -capacitate, noua capacitate a produsului
     * Produsul cu seria data va avea campurile date dupa executia functiei
     */
    void modifica(const string& serie, const string& tip, const string& nume, const string& producator, int pret, int capacitate);

    /*
     * Functia cauta si returneaza un produs din lista de produse sau arunca exceptie daca nu exista
     * Parametrii:
     *  -serie, reprezinta seria produsului cautat
     */
    Produs& cauta(const string& serie);

    /*
     * Functia filtreaza produsele dupa un pret dat
     * Parametrii:
     *  -pret, pretul dupa care se filtreaza
     * Se returneaza un vector cu toate produsele care au pretul dat
     */
    vector<Produs> filtrare_pret(int pret);

    /*
     * Functia filtreaza produsele dupa o capacitate data
     * Parametrii:
     *  -capacitate, reprezinta capactitatea dupa care se filtreaza
     * Se returneaza un vector cu toate produsele care au capacitatea data
     */
    vector<Produs> filtrare_capacitate(int capacitate);

    /*
     * Funcita filtreaza produsele dupa un producator dat
     * Parametrii:
     *  -producator, reprezinta producatorul dupa care se filtreaza
     * Se returneaza un vector cu toate produsele care au producatorul dat
     */
    vector<Produs> filtrare_producator(const string& producator);

    /*
     * Functie generica pentru sortare
     * Parametrii:
     *  -cmp, reprezinta o functie care compara cei doi parametrii de tip produs, dupa un anumit criteriu
     * Functia returneaza vectorul de produse sortat corespunzator functiei de sortare
     */
    vector<Produs> sortare(std::function<bool(const Produs&, const Produs&)> cmp);

    /*
     * Functia efectueaza operatia de undo asupra listei de produse
     */
    void do_undo();

    /*
     * Functia efectueaza operatia de redo asupra listei de produse
     */
    void do_redo();

    /*
     * Functia returneaza toate produsele fara sa realizeze o copie a vectorului
     */
    const vector<Produs>& get_all();

    /*
     * Functia returneaza o copie a vectorului de produse
     */
    vector<Produs> get_copy();

    /*
     * Functia adauga produsul cu seria data in cos
     * Parametrii:
     *  -serie, reprezinta seria produsului care se adauga
     * Se arunca exceptie daca nu exista niciun produs cu aceasta serie
     */
    void adauga_cos(const string& serie);

    /*
     * Functia de stergere a produsului cu seria data din cos
     * Parametrii:
     *  -serie, reprezinta seria produsului care se doreste a fi sters
     * Se arunca exceptie daca nu exista niciun produs cu aceasta serie
     */
    void sterge_cos(const string& serie);


    /*
     * Functia de golire a cosului de cumparaturi
     * Vectorul de produse care reprezinta cosul se goleste
     */
    void golire_cos();

    /*
     * Functia de adaugare de produse random in cos
     * Parametrii:
     *  -dim, reprezinta numarul de produse care se doresc a fi adaugate
     *  -vect, reprezinta vectorul de produse din care se vor lua random "dim" produse
     * In vectorul "cos" vor fi adaugate "dim" produse random din "vect"
     */
    void populare_cos(int dim, const vector<Produs>&  vect);

    /*
     * Functia returneaza vectorul de produse corespunzator cosului de cumparaturi
     */
    const vector<Produs>& get_cos();

    /*
     * Functia returneaza pretul total al produselor din cos
     */
    int get_total() const;

    ~Service() = default;
};


#endif //PRODUSE_SERVICE_H
