#ifndef MODEL_H
#define MODEL_H

#include <QMap>
#include <QAbstractItemModel>
#include "category.h"
#include "datamanager.h"

class DataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    DataModel(DataManager* m, QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Book getBook(const int& row) const;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    QString getCategoryName(const int& id);
    QMap<int, Category>& getCategories();
    bool addBook(QList<QVariant> bookParam);
private:
    DataManager* m;
signals:
    void updateBookInfo(const QModelIndex&);
};

#endif // MODEL_H
