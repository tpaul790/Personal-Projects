//
// Created by Titieni Paul on 25.07.2024.
//

#ifndef PRODUSE_TABLEMODEL_H
#define PRODUSE_TABLEMODEL_H


#include <QAbstractTableModel>
#include <utility>
#include <vector>
#include <map>
#include "../Domain/Produs.h"
#include <QBrush>

using namespace std;

class TableModel : public QAbstractTableModel{
private:
//Q_OBJECT
    vector<Produs> produse;
    string serie;
public:
    TableModel(vector<Produs> produse) : produse(std::move(produse)){}

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation,int role) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    void setProduse(vector<Produs> produs);

    void setSerie(const string& s);

};


#endif //PRODUSE_TABLEMODEL_H
