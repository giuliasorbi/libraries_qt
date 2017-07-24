#include <QtWidgets>
#include <QMap>
#include "catmodel.h"
#include "datamanager.h"
//#include "mainwindow.h"

CatModel::CatModel(DataManager* m, QObject *parent)
    : m(m),
      QAbstractListModel(parent)
{}


QVariant CatModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (index.row() >= m->categories.size()) {
        return QVariant();
    }
    auto count = 0;
    for (const auto& c : m->categories) {
        if (count == index.row()) {
            return c.name();
        }
        count++;
    }

    return QVariant();
}


int CatModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0) {
        return 0;
    }
    return m->categories.size();

}


bool CatModel::setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole)
{

    if (role != Qt::DisplayRole) {
            return false;
    }

    QList<QVariant> list = value.toList(); // name, description, author, image, category
    auto count = 0;
    auto id = 0;
    for (const auto& c : m->categories) {
        if (count == index.row()) {
            id = c.id();
            break;
        }
        count++;
    }

    if (!m->categories.contains(id)) {
        return false;
    }
    if (m->categories.value(id).name() != list.at(0).toString()) {
        m->categories[id].setName(list.at(0).toString());
    }
    if (m->categories.value(id).description() != list.at(1).toString()) {
        m->categories[id].setDescription(list.at(1).toString());
    }

    emit (dataChanged(index,index));
    emit (updateCatInfo(index));


    return true;
}

QVariant CatModel::headerData(int section, Qt::Orientation orientation, int role) const {
    Q_UNUSED(section)

    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Horizontal) {
        return QString("Categories");
    }
    return QVariant();
}


bool CatModel::removeRows(int row, int count, const QModelIndex &parent )
{

    if (row == 0) { // uncategorized book
        return false;
    }

    beginRemoveRows(parent, row, row+count-1);

    auto c = 0;
    for (const auto& cat : m->categories) {
        if (c == row) {
            for (auto& b : m->categories.value(cat.id()).books()) {
               m->books[b].setCategory(0); // uncategorized book
               m->categories[0].addBook(b);
            }

            m->categories.remove(cat.id());
            break;
        }
        c++;
    }

    endRemoveRows();

    emit (dataChanged(parent, parent));

    QModelIndex i = index(row, 0, QModelIndex());
    if (!i.isValid()) {
        i = index(row-1, 0, QModelIndex());
    }
    emit(updateCatInfo(i));
    return true;
}

QString CatModel::getCategoryDesc(const int& row)
{
    if (row >= m->categories.size()) {
        return "";
    }
    auto count = 0;
    for (const auto& cat : m->categories) {
        if (count == row) {
            return m->categories.value(cat.id()).description();
        }
        count++;
    }
    return "";
}

QStringList CatModel::getBookList(const int& row)
{
    QStringList list;
    auto count = 0;
    for (const auto& cat : m->categories) {
        if (count == row) {
            for(const auto& b : m->categories.value(cat.id()).books()) {
                list.append(m->books.value(b).name());
            }
        }
        count++;
    }

    return list;
}


bool CatModel::addCategory(QList<QVariant> categoryParam) {
    auto id = 1;
    if (!m->categories.empty()) {
        id = m->categories.keys().last();
        id++;
    }

    beginInsertRows(QModelIndex(), m->categories.size()-1, m->categories.size()-1);
    m->categories.insert(id, Category(id, categoryParam.at(0).toString(), categoryParam.at(1).toString()));
    endInsertRows();
    return true;
}

