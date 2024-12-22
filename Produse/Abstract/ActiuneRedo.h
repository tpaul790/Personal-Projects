//
// Created by Titieni Paul on 06.08.2024.
//

#ifndef PRODUSE_ACTIUNEREDO_H
#define PRODUSE_ACTIUNEREDO_H
#include "../Domain/Produs.h"
#include "../Repo/RepoFile.h"

class ActiuneRedo {
public:
    virtual void do_redo() = 0;
    virtual ~ActiuneRedo() = default;
};

class AdaugaRedo : public ActiuneRedo{
private:
    RepoFile& repo;
    Produs produs;
public:
    AdaugaRedo(RepoFile& repo, Produs prod) : repo{repo}, produs{std::move(prod)}{};

    void do_redo() override;
};

class StergeRedo: public ActiuneRedo{
private:
    RepoFile& repo;
    Produs produs;
public:
    StergeRedo(RepoFile& repo, Produs prod) : repo{ repo }, produs{ std::move(prod) }{};

    void do_redo() override;
};

class ModificaRedo : public ActiuneRedo{
private:
    RepoFile& repo;
    Produs produs;
public:
    ModificaRedo(RepoFile& repo, Produs prod) : repo{repo}, produs{std::move(prod)}{};

    void do_redo() override;
};


#endif //PRODUSE_ACTIUNEREDO_H
