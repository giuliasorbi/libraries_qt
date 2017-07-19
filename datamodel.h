#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QAbstractItemModel>
#include "category.h"
#include "datamanager.h"

class DataModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    DataModel(/*QMap<int, Category>* cat, */ QObject *parent = nullptr);
//    Category* getItem(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const { return 1; }
    QModelIndex parent(const QModelIndex &index) const;

private:
    DataManager m;

//private:
//    QMap<int, Category>* m_categories;

};

#endif // MODEL_H
