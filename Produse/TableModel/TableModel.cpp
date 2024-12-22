//
// Created by Titieni Paul on 25.07.2024.
//

#include "TableModel.h"

int TableModel::rowCount(const QModelIndex &parent) const{
    return produse.size();
}

int TableModel::columnCount(const QModelIndex &parent) const {
    return 6;
}

void TableModel::setProduse(vector<Produs> prods) {
    this->produse = std::move(prods);
    const QModelIndex& topLeft = createIndex(0, 0);
    const QModelIndex& bottomRight = createIndex(rowCount(), 0);
    emit layoutChanged();
    emit dataChanged(topLeft, bottomRight);
}

void TableModel::setSerie(const string &s) {
    this->serie = s;
    const QModelIndex& topLeft = createIndex(0, 0);
    const QModelIndex& bottomRight = createIndex(rowCount(), 0);
    emit layoutChanged();
    emit dataChanged(topLeft, bottomRight);
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    auto col = index.column();
    auto produs = produse[index.row()];
    auto nume = produs.get_nume();
    auto tip = produs.get_tip();
    auto pret = produs.get_pret();
    auto s = produs.get_serie();
    auto producator = produs.get_producator();
    auto capacitate = produs.get_capacitate();
    if(role == Qt::DisplayRole){
        //qDebug()<<"col: "<<index.column()<<' '<<"row: "<<index.row();
        if(col == 0)
            return QString::fromStdString(s);
        if(col == 1)
            return QString::fromStdString(tip);
        if(col == 2)
            return QString::fromStdString(nume);
        if(col == 3)
            return QString::fromStdString(producator);
        if(col == 4)
            return QString::number(pret);
        if(col == 5)
            return QString::number(capacitate);
    }else if(role == Qt::BackgroundRole){
        if(serie == s){
            QBrush br{Qt::red};
            return br;
        }
    }
    return QVariant{};
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            if(section == 0)
                return QString("Serie");
            else if(section == 1)
                return QString("Tip");
            else if(section == 2)
                return QString("Nume");
            else if(section == 3)
                return QString("Producator");
            else if(section == 4)
                return QString("Pret(*100 LEI)");
            else if(section == 5)
                return QString("Capacitate(GB)");
        }
        else
            return QString("%1").arg(section+1);
    }
    return QVariant{};
}

