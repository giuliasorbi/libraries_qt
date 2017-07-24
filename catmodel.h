#ifndef CATMODEL_H
#define CATMODEL_H

#include <QMap>
#include <QAbstractItemModel>
#include "category.h"
#include "datamanager.h"

class CatModel : public QAbstractListModel
{
    Q_OBJECT
public:
    CatModel(DataManager* m, QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    QString getCategoryDesc(const int& row);
    QStringList getBookList(const int& row);
    bool addCategory(QList<QVariant> categoryParam);
private:
    DataManager* m;
signals:
    void updateCatInfo(const QModelIndex&);

};


#endif // CATMODEL_H
