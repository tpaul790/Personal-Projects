//
// Created by Titieni Paul on 09.08.2024.
//

#ifndef PRODUSE_OBSERVABLE_H
#define PRODUSE_OBSERVABLE_H
#include "Observer.h"
#include <vector>
using std::vector;

class Observable {
private:
    vector<Observer*> inscrisi;
public:
    Observable() = default;

    /*
     * Functia adauga un observator in lista de observatori
     * Parametrii:
     *  -obs, reprezinta un pointer catre observatorul pe care dorim sa-l inscriem
     * Pointerul obs se va afla in lista de observatori
     */
    void inscrie(Observer* obs);

    /*
     * Functia notifica toti observatorii inscrisi
     * Toti observatorii inscrisi vor apela functia lor proprie pentru update
     */
    void notify();

    /*
     * Functia anuleaza inscrierea unui observator
     * Parametrii:
     *  -obs, reprezinta un pointer catre observatorul a carui inscriere dorim sa o anulam
     * Pointerul ons nu se va mai afla in lista de observatori
     */
    void anuleaza(Observer* obs);

    /*
     * Destructorul va apela destructorii pentru fiecare obiect observer din lista
     */
    ~Observable(){
        for(auto& obs : inscrisi){
            delete obs;
        }
    }
};


#endif //PRODUSE_OBSERVABLE_H
