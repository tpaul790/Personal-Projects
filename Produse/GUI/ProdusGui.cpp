//
// Created by Titieni Paul on 25.07.2024.
//

#include "ProdusGui.h"

void ProdusGui::init_gui() {
    this->setLayout(main_ly);
    vw->setModel(tabel);
    vw->setSelectionBehavior(QAbstractItemView::SelectRows);
    pret_txt->setMinimum(1);
    pret_txt->setMaximum(99);
    auto* tabel_ly = new QVBoxLayout;
    auto* simple_btn_ly = new QVBoxLayout;
    auto* special_btn_ly = new QHBoxLayout;
    auto* cos_btn_ly = new QVBoxLayout;
    auto* special_cos_btn_ly = new QHBoxLayout;

    auto* drept_ly = new QVBoxLayout;
    auto* form_btn_ly = new QHBoxLayout;
    auto* sort_combo_ly = new QHBoxLayout;
    auto* sort_btn_ly = new QVBoxLayout;
    auto* filtrare_btn_ly = new QVBoxLayout;
    auto* filtrare_combo_ly = new QHBoxLayout;
    auto* form_ly = new QVBoxLayout;
    auto* form = new QFormLayout;
    auto* slider_combo_ly = new QVBoxLayout;
    auto* slider_ly = new QHBoxLayout;

    form_ly->addLayout(form);
    form_ly->addLayout(slider_combo_ly);
    form->addRow("Serie->",serie_txt);
    form->addRow("Tip->",tip_txt);
    form->addRow("Nume->",nume_txt);
    form->addRow("Producator->",producator_txt);
    form->addRow("Pret->",slider_ly);
    form->addRow("Capacitate->",capacitate_txt);

    slider_ly->addWidget(pret_txt);
    slider_ly->addWidget(slider_lb);
    slider_lb->setText(QString::fromStdString(to_string(pret_txt->value())));

    capacitate_txt->addItem("1");
    capacitate_txt->addItem("64");
    capacitate_txt->addItem("128");
    capacitate_txt->addItem("256");
    capacitate_txt->addItem("512");
    capacitate_txt->addItem("1024");

    for(int i = 1;i <= 10; i++)
        nr_populare->addItem(QString::fromStdString(std::to_string(i)));

    main_ly->addLayout(tabel_ly);
    tabel_ly->addLayout(special_cos_btn_ly);
    tabel_ly->addWidget(vw);
    tabel_ly->addWidget(inchide);

    drept_ly->addLayout(form_btn_ly);
    main_ly->addLayout(drept_ly);
    form_btn_ly->addLayout(form_ly);
    form_btn_ly->addLayout(simple_btn_ly);
    form_btn_ly->addLayout(cos_btn_ly);

    sort_btn_ly->addWidget(sortare);
    sort_combo_ly->addWidget(ordine);
    ordine->addItem("crescator");
    ordine->addItem("descrescator");
    sort_combo_ly->addWidget(tip_sortare);
    tip_sortare->addItem("producator");
    tip_sortare->addItem("pret");
    tip_sortare->addItem("capacitate");
    sort_btn_ly->addLayout(sort_combo_ly);

    filtrare_btn_ly->addWidget(filtrare);
    filtrare_combo_ly->addWidget(tip_filtrare);
    tip_filtrare->addItem("producator");
    tip_filtrare->addItem("pret");
    tip_filtrare->addItem("capacitate");
    filtrare_btn_ly->addLayout(filtrare_combo_ly);

    special_btn_ly->addLayout(sort_btn_ly);
    special_btn_ly->addLayout(filtrare_btn_ly);

    drept_ly->addLayout(special_btn_ly);

    simple_btn_ly->addWidget(adauga);
    simple_btn_ly->addWidget(sterge);
    simple_btn_ly->addWidget(cauta);
    simple_btn_ly->addWidget(modifica);
    simple_btn_ly->addWidget(undo);
    simple_btn_ly->addWidget(redo);

    cos_btn_ly->addWidget(adauga_cos);
    cos_btn_ly->addWidget(sterge_cos);
    cos_btn_ly->addWidget(populare);
    cos_btn_ly->addWidget(nr_populare);
    cos_btn_ly->addWidget(golire);

    special_cos_btn_ly->addWidget(deschide_cos);
    special_cos_btn_ly->addWidget(statistici);
}

void ProdusGui::connect() {

    QObject::connect(vw->selectionModel(),&QItemSelectionModel::selectionChanged,[this](){
        auto row = vw->selectionModel()->selectedIndexes().at(0).row();
        auto cell1 = vw->model()->index(row,0);
        auto cell2 = vw->model()->index(row,1);
        auto cell3 = vw->model()->index(row,2);
        auto cell4 = vw->model()->index(row,3);
        auto cell5 = vw->model()->index(row,4);
        auto cell6 = vw->model()->index(row,5);
        auto serie = vw->model()->data(cell1,Qt::DisplayRole).toString();
        auto tip = vw->model()->data(cell2,Qt::DisplayRole).toString();
        auto nume = vw->model()->data(cell3,Qt::DisplayRole).toString();
        auto producator = vw->model()->data(cell4,Qt::DisplayRole).toString();
        auto pret = vw->model()->data(cell5,Qt::DisplayRole).toString();
        auto capacitate = vw->model()->data(cell6,Qt::DisplayRole).toInt();
        serie_txt->setText(serie);
        tip_txt->setText(tip);
        nume_txt->setText(nume);
        producator_txt->setText(producator);
        pret_txt->setValue(pret.toInt());
        int idx = 0;
        if(capacitate==1)
            idx=0;
        else {
            int cnt = 1;
            for (int i = 64; i <= 1024; i *= 2) {
                if (capacitate == i)
                    idx = cnt;
                cnt++;
            }
        }
        capacitate_txt->setCurrentIndex(idx);
    });

    QObject::connect(adauga,&QPushButton::clicked,[this](){
        if(serie_txt->text().isEmpty() or tip_txt->text().isEmpty() or nume_txt->text().isEmpty() or producator_txt->text().isEmpty())
            QMessageBox::warning(this,"Error","Va rog sa completati cu date toate campurile!");
        else{
            try{
                auto serie = serie_txt->text().toStdString();
                auto tip = tip_txt->text().toStdString();
                auto nume = nume_txt->text().toStdString();
                auto producator = producator_txt->text().toStdString();
                auto pret = pret_txt->value();
                auto capacitate = capacitate_txt->currentText().toInt();
                service.adauga(serie,tip,nume,producator,pret,capacitate);
                tabel->setProduse(service.get_all());
            }catch (RepoException& e){
                QMessageBox::warning(this,"Error",QString::fromStdString(e.get_mesaj()));
            }
            catch (ServiceException& e){
                QMessageBox::warning(this,"Error",QString::fromStdString(e.get_mesaj()));
            }
        }
    });

    QObject::connect(sterge,&QPushButton::clicked,[this](){
        if(serie_txt->text().isEmpty())
            QMessageBox::warning(this,"Error","Va rog sa introduceti seria produsului pe care doriti sa-l stergeti!");
        else{
            try{
                auto serie = serie_txt->text().toStdString();
                service.sterge(serie);
                tabel->setProduse(service.get_all());
            }catch (RepoException& e){
                QMessageBox::warning(this,"Error",QString::fromStdString(e.get_mesaj()));
            }
            catch (ServiceException& e){
                QMessageBox::warning(this,"Error",QString::fromStdString(e.get_mesaj()));
            }
        }
    });

    QObject::connect(modifica,&QPushButton::clicked,[this](){
       if(serie_txt->text().isEmpty()){
           QMessageBox::warning(this,"Error","Va rog sa introduceti seria produsului pe care doriti sa-l modificati!");
       }else{
           if(tip_txt->text().isEmpty() or nume_txt->text().isEmpty() or producator_txt->text().isEmpty())
               QMessageBox::warning(this,"Error","Va rog sa completati noile date ale produsului!");
           try{
               auto serie = serie_txt->text().toStdString();
               auto tip = tip_txt->text().toStdString();
               auto nume = nume_txt->text().toStdString();
               auto producator = producator_txt->text().toStdString();
               auto pret = pret_txt->value();
               auto capacitate = capacitate_txt->currentText().toInt();
               service.modifica(serie,tip,nume,producator,pret,capacitate);
               tabel->setProduse(service.get_all());
           }catch (RepoException& e){
               QMessageBox::warning(this,"Error",QString::fromStdString(e.get_mesaj()));
           }catch (ServiceException& e){
               QMessageBox::warning(this,"Error",QString::fromStdString(e.get_mesaj()));
           }
       }
    });

    QObject::connect(inchide,&QPushButton::clicked,[this](){
        this->close();
    });

    QObject::connect(pret_txt,&QSlider::valueChanged,[this](){
        slider_lb->setText(QString::fromStdString(to_string(pret_txt->value())));
    });

    QObject::connect(sortare,&QPushButton::clicked,[this](){
        auto ord = ordine->currentText().toStdString();
        auto tip = tip_sortare->currentText().toStdString();
        if(ord == "crescator"){
            if(tip == "pret"){
                tabel->setProduse(service.sortare(crescator_pret));
            }
            else if(tip == "capacitate"){
                tabel->setProduse(service.sortare(crescator_capacitate));
            }
            else{
                tabel->setProduse(service.sortare(crescator_producator));
            }
        }else{
            if(tip == "pret"){
                tabel->setProduse(service.sortare(descrescator_pret));
            }
            else if(tip == "capacitate"){
                tabel->setProduse(service.sortare(descrescator_capacitate));
            }
            else{
                tabel->setProduse(service.sortare(descrescator_producator));
            }
        }
    });

    QObject::connect(filtrare,&QPushButton::clicked,[this](){
        auto tip = tip_filtrare->currentText().toStdString();
        if(tip == "producator" and producator_txt->text().isEmpty())
            QMessageBox::warning(this,"Error","Va rog sa introduceti un producator in textfield-ul destinat!");
        else {
            auto* gui = new FiltreGui{service,tip};
            if(tip == "producator") {
                gui->set_producator(producator_txt->text().toStdString());
            }else if(tip == "pret"){
                gui->set_pret(pret_txt->value());
            }else{
                gui->set_capacitate(capacitate_txt->currentText().toInt());
            }
            gui->show();
        }
    });

    QObject::connect(undo,&QPushButton::clicked,[this](){
       try{
           service.do_undo();
           tabel->setProduse(service.get_all());
       } catch (ServiceException& e){
           QMessageBox::warning(this, "Error", QString::fromStdString(e.get_mesaj()));
       }catch (RepoException& e){
           QMessageBox::warning(this,"Error","Nu se poate face undo!");
       }
    });

    QObject::connect(redo,&QPushButton::clicked,[this](){
       try {
           service.do_redo();
           tabel->setProduse(service.get_all());
       } catch (ServiceException& e){
           QMessageBox::warning(this,"Error",QString::fromStdString(e.get_mesaj()));
       }catch (RepoException& e){
           QMessageBox::warning(this,"Error","Nu se poate face redo!");
       }
    });

    QObject::connect(cauta,&QPushButton::clicked,[this](){
        if(serie_txt->text().isEmpty()){
            QMessageBox::warning(this,"Error","Va rog sa completati in textfield ul destinat, seria produsului pe care il cautati!");
        }else{
            try{
                auto produs = service.cauta(serie_txt->text().toStdString());
                //setez background ul rosu pentru produsul cu seria data
                tabel->setSerie(serie_txt->text().toStdString());
                //completez toate textfield-urile
                nume_txt->setText(QString::fromStdString(produs.get_nume()));
                tip_txt->setText(QString::fromStdString(produs.get_tip()));
                producator_txt->setText(QString::fromStdString(produs.get_producator()));
                pret_txt->setValue(produs.get_pret());
                capacitate_txt->setCurrentText(QString::fromStdString(to_string(produs.get_capacitate())));
            }catch (RepoException& e){
                QMessageBox::warning(this,"Error",QString::fromStdString(e.get_mesaj()));
            }
        }
    });

    QObject::connect(adauga_cos,&QPushButton::clicked,[this](){
       if(serie_txt->text().isEmpty()){
           QMessageBox::warning(this,"Error","Va rog sa introduceti seria produsului pe care doriti sa-l adaugati!");
       }else{
           try{
               service.adauga_cos(serie_txt->text().toStdString());
           }catch (ServiceException& e){
               QMessageBox::warning(this,"Error",QString::fromStdString(e.get_mesaj()));
           }catch (RepoException& e){
               QMessageBox::warning(this,"Error",QString::fromStdString(e.get_mesaj()));
           }
       }
    });

    QObject::connect(sterge_cos,&QPushButton::clicked,[this](){
        if(serie_txt->text().isEmpty()){
            QMessageBox::warning(this,"Error","Va rog sa introduceti seria produsului pe care doriti sa-l stergeti!");
        }else{
            try{
                service.sterge_cos(serie_txt->text().toStdString());
            }catch (ServiceException& e){
                QMessageBox::warning(this,"Error",QString::fromStdString(e.get_mesaj()));
            }catch (RepoException& e){
                QMessageBox::warning(this,"Error",QString::fromStdString(e.get_mesaj()));
            }
        }
    });

    QObject::connect(populare,&QPushButton::clicked,[this](){
        service.populare_cos(nr_populare->currentText().toInt(),service.get_all());
    });

    QObject::connect(golire,&QPushButton::clicked,[this](){
        service.golire_cos();
    });

    QObject::connect(deschide_cos,&QPushButton::clicked,[this](){
        auto ob = new CosGui{service};
        ob->show();
    });

    QObject::connect(statistici,&QPushButton::clicked,[this](){
        auto ob = new StatisticiGui{service};
        ob->show();
    });

}
