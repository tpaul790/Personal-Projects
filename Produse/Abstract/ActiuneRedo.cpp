//
// Created by Titieni Paul on 06.08.2024.
//

#include "ActiuneRedo.h"

void AdaugaRedo::do_redo() {
    repo.adauga(produs);
}

void StergeRedo::do_redo() {
    repo.sterge(produs.get_serie());
}

void ModificaRedo::do_redo() {
    repo.modifica(produs.get_serie(),produs);
}