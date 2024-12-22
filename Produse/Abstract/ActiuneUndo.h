//
// Created by Titieni Paul on 05.08.2024.
//

#ifndef PRODUSE_ACTIUNEUNDO_H
#define PRODUSE_ACTIUNEUNDO_H

#include "../Domain/Produs.h"
#include "../Repo/RepoFile.h"

class ActiuneUndo {
public:
    virtual void doUndo() = 0;
    virtual string tipActiune() = 0;
    virtual Produs getProdus() = 0;
    virtual ~ActiuneUndo() = default;
};

class AdaugaUndo : public ActiuneUndo{
private:
    RepoFile& repo;
    Produs produs;
public:
    AdaugaUndo(RepoFile& repo ,const Produs& prod) : repo{repo}, produs{prod}{};

    void doUndo() override;

    string tipActiune() override;

    Produs getProdus() override;
};

class StergeUndo : public ActiuneUndo{
private:
    RepoFile& repo;
    Produs produs;
public:
    StergeUndo(RepoFile& repo, const Produs& prod) : repo{repo}, produs{prod}{};

    void doUndo() override;

    string tipActiune() override;

    Produs getProdus() override;
};

class ModificaUndo : public ActiuneUndo{
private:
    RepoFile& repo;
    Produs produs_vechi,produs_nou;
public:
    ModificaUndo(RepoFile& repo, const Produs& vechi, const Produs& nou) : repo{repo}, produs_vechi{vechi}, produs_nou{ nou}{};

    void doUndo() override;

    string tipActiune() override;

    Produs getProdus() override;
};


#endif //PRODUSE_ACTIUNEUNDO_H
