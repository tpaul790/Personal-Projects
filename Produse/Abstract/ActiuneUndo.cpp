//
// Created by Titieni Paul on 05.08.2024.
//

#include "ActiuneUndo.h"

//adauga
void AdaugaUndo::doUndo() {
    repo.sterge(produs.get_serie());
}

string AdaugaUndo::tipActiune() {
    return ("adauga");
}

Produs AdaugaUndo::getProdus() {
    return produs;
}

//sterge
void StergeUndo::doUndo() {
    repo.adauga(produs);
}

string StergeUndo::tipActiune() {
    return ("sterge");
}

Produs StergeUndo::getProdus() {
    return produs;
}

//modifica
void ModificaUndo::doUndo() {
    repo.modifica(produs_vechi.get_serie(),produs_vechi);
}

string ModificaUndo::tipActiune() {
    return ("modifica");
}

Produs ModificaUndo::getProdus() {
    return produs_nou;
}
