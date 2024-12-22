//
// Created by Titieni Paul on 24.07.2024.
//

#include "teste.h"
#include "assert.h"
void test_validator(){
    Validator validator;
    assert(!validator.validare_serie("").empty());
    assert(validator.validare_serie("FA12HFAD32").empty());

    assert(validator.validare_tip("telefon").empty());
    assert(!validator.validare_tip("lactate").empty());

    assert(validator.validare_nume("iphone").empty());
    assert(!validator.validare_nume("").empty());

    assert(validator.validare_producator("apple").empty());
    assert(!validator.validare_producator("logitec").empty());

    assert(validator.validare_pret(10).empty());
    assert(!validator.validare_pret(-1).empty());

    assert(validator.validare_capacitate(128).empty());
    assert(!validator.validare_capacitate(31).empty());
}

void test_domain(){
    Produs p1{"a","b","c","d",12,128};
    assert(p1.get_serie()=="a");
    assert(p1.get_tip()=="b");
    assert(p1.get_nume()=="c");
    assert(p1.get_producator()=="d");
    assert(p1.get_pret()==12);
    assert(p1.get_capacitate()==128);

    p1.set_tip("a");
    assert(p1.get_tip()=="a");
    p1.set_nume("a");
    assert(p1.get_nume()=="a");
    p1.set_producator("a");
    assert(p1.get_producator()=="a");
    p1.set_pret(21);
    assert(p1.get_pret()==21);
    p1.set_capacitate(64);
    assert(p1.get_capacitate()==64);
}

void test_adauga_repo(){
    RepoFile repo{"test.txt"};
    assert(repo.get_all().size()==10);
    Produs p1{"a","b","c","d",12,128};
    repo.adauga(p1);
    assert(repo.get_all().size()==11);
    try{
        repo.adauga(p1);
        assert(false);
    }catch(RepoException){
        assert(true);
    }
}

void test_modifica_repo(){
    RepoFile repo{"test.txt"};
    assert(repo.get_all().size()==11);
    Produs p2{"x","x","x","x",21,64};
    repo.modifica("a",p2);
    auto p = repo.cauta("a");
    assert(p.get_serie()=="a");
    assert(p.get_tip()=="x");
    assert(p.get_nume()=="x");
    assert(p.get_producator()=="x");
    assert(p.get_pret()==21);
    assert(p.get_capacitate()==64);

    try{
        repo.modifica("x",p2);
        assert(false);
    }catch (RepoException){
        assert(true);
    }

    try{
        repo.cauta("x");
        assert(false);
    }catch (RepoException){
        assert(true);
    }
}

void test_sterge_repo(){
    RepoFile repo{"test.txt"};
    assert(repo.get_all().size()==11);
    repo.sterge("a");
    assert(repo.get_all().size()==10);
    try{
        repo.sterge("a");
        assert(false);
    }catch (RepoException){
        assert(true);
    }
}

void test_repo(){
    test_adauga_repo();
    test_modifica_repo();
    test_sterge_repo();
}

void test_adauga_cos(){
    CosProduse cos;
    Produs p2{"x","x","x","x",21,64};
    assert(cos.get_all().empty());
    cos.adauga(p2);
    assert(cos.get_all().size()==1);
    cos.adauga(p2);
    cos.adauga(p2);
    assert(cos.get_all().size()==3);
}

void test_sterge_cos(){
    CosProduse cos;
    Produs p2{"x","x","x","x",21,64};
    cos.adauga(p2);
    cos.adauga(p2);
    cos.adauga(p2);
    assert(cos.get_all().size()==3);

    cos.sterge(p2);
    assert(cos.get_all().size()==2);
    cos.sterge(p2);
    cos.sterge(p2);
    assert(cos.get_all().empty());
}

void test_goleste_cos(){
    CosProduse cos;
    Produs p2{"x","x","x","x",21,64};
    cos.adauga(p2);
    cos.adauga(p2);
    cos.adauga(p2);
    assert(cos.get_all().size()==3);
    cos.goleste();
    assert(cos.get_all().empty());
}

void test_populare_cos(){
    CosProduse cos;
    Produs p2{"x","x","x","x",21,64};
    vector<Produs> vect;
    vect.push_back(p2);
    cos.populare(3,vect);
    assert(cos.get_all().size()==3);
    cos.populare(3,vect);
    assert(cos.get_all().size()==6);
}

void test_cos(){
    test_adauga_cos();
    test_sterge_cos();
    test_goleste_cos();
    test_populare_cos();
}

void test_service() {
    RepoFile repo{"test.txt"};
    CosProduse cos;
    Validator validator;
    Service service{repo, cos, validator};
    assert(service.get_all().size() == 10);
    //adauga
    try {
        service.adauga("a", "a", "a", "a", -1, 0);
        assert(false);
    } catch (ServiceException &e) {
        assert(true);
    }
    service.adauga("ZLSJOKK239", "casti", "airbuds", "samsung", 6, 1);
//    modifica
    service.modifica("ZLSJOKK239", "casti", "airbuds", "samsung", 6, 128);
//    sterge
    auto p = service.cauta("ZLSJOKK239");
    assert(p.get_capacitate() == 128);
    service.sterge("ZLSJOKK239");
    try {
        service.sterge("ZLSJOKK239");
        assert(false);
    } catch (RepoException &e) {
        assert(true);
    }
    //sorteaza
    auto sortat_pret = service.sortare(crescator_pret);
    assert(sortat_pret.at(0).get_pret() == 6);
    assert(sortat_pret.back().get_pret() == 67);
    sortat_pret = service.sortare(descrescator_pret);
    assert(sortat_pret.at(0).get_pret() == 67);
    assert(sortat_pret.back().get_pret() == 6);

    auto sortat_capacitate = service.sortare(crescator_capacitate);
    assert(sortat_capacitate.at(0).get_capacitate() == 1);
    assert(sortat_capacitate.back().get_capacitate() == 1024);
    sortat_capacitate = service.sortare(descrescator_capacitate);
    assert(sortat_capacitate.at(0).get_capacitate() == 1024);
    assert(sortat_capacitate.back().get_capacitate() == 1);

    auto sortat_producator = service.sortare(crescator_producator);
    assert(sortat_producator.at(0).get_producator() == "apple");
    assert(sortat_producator.back().get_producator() == "samsung");
    sortat_producator = service.sortare(descrescator_producator);
    assert(sortat_producator.at(0).get_producator() == "samsung");
    assert(sortat_producator.back().get_producator() == "apple");
    //filtrare
    auto filtru_pret = service.filtrare_pret(67);
    assert(filtru_pret.size() == 2);
    for (const auto &prod: filtru_pret)
        assert(prod.get_pret() == 67);
    auto filtru_producator = service.filtrare_producator("apple");
    assert(filtru_producator.size() == 7);
    for (const auto &prod: filtru_producator)
        assert(prod.get_producator() == "apple");
    auto filtru_capacitate = service.filtrare_capacitate(1024);
    assert(filtru_capacitate.size() == 2);
    for (const auto &prod: filtru_capacitate)
        assert(prod.get_capacitate() == 1024);
    //undo
    service.adauga("ZLSJOKK238", "casti", "airpods", "apple", 10, 64);
    assert(service.get_all().size() == 11);
    service.sterge("ZLSJOKK238");
    assert(service.get_all().size() == 10);
    try{
        service.cauta("ZLSJOKK238");
        assert(false);
    }catch (RepoException& e){
        assert(true);
    }
    service.do_undo();
    assert(service.get_all().size() == 11);
    try{
        service.cauta("ZLSJOKK238");
        assert(true);
    }catch (RepoException& e){
        assert(false);
    }
    service.do_undo();
    assert(service.get_all().size() == 10);
    try{
        service.cauta("ZLSJOKK238");
        assert(false);
    }catch (RepoException& e){
        assert(true);
    }
    service.adauga("ZLSJOKK238", "casti", "airpods", "apple", 10, 64);
    assert(service.cauta("ZLSJOKK238").get_capacitate()==64);
    service.modifica("ZLSJOKK238", "casti", "airpods", "apple", 10, 1);
    assert(service.cauta("ZLSJOKK238").get_capacitate()==1);
    service.do_undo();
    assert(service.cauta("ZLSJOKK238").get_capacitate()==64);
    service.sterge("ZLSJOKK238");

    //redo
    service.adauga("1a", "casti", "airpods", "apple", 10, 64);
    service.sterge("1a");
    assert(service.get_all().size() == 10);
    service.do_undo();
    assert(service.get_all().size() == 11);
    service.do_redo();
    assert(service.get_all().size() == 10);
    try{
        service.do_undo();//incearca sa stearga un produs inexsitent
        assert(false);
    }catch (RepoException& e){
        assert(true);
    }
    try{
        service.do_redo();
        assert(false);
    }catch (RepoException& e){
        assert(true);
    }
    //cos
    assert(service.get_cos().empty());
    service.adauga("1a" ,"casti" ,"airbuds", "samsung" ,6 ,1);
    service.adauga_cos("1a");
    try{
        service.adauga_cos("1c");
        assert(false);
    }catch (RepoException&){
        assert(true);
    }
    assert(service.get_cos().size()==1);
    service.sterge_cos("1a");
    try{
        service.sterge_cos("1c");
        assert(false);
    }catch (RepoException&){
        assert(true);
    }
    assert(service.get_cos().empty());
    service.populare_cos(3,service.get_all());
    assert(service.get_cos().size()==3);
    service.golire_cos();
    assert(service.get_cos().empty());
    service.sterge("1a");
}

void test_all(){
    test_validator();
    test_domain();
    test_repo();
    test_cos();
    test_service();
}