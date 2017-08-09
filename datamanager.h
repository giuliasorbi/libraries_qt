#include <QtWidgets>
#include <QMap>
#include "datamodel.h"
#include "datamanager.h"
//#include "mainwindow.h"

DataModel::DataModel(DataManager* m, QObject *parent)
    : m(m),
      QAbstractListModel(parent)
{

}


QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (index.row() >= m->books.size()) {
        return QVariant();
    }
    auto count = 0;
    for (const auto& b : m->books) {
        if (count == index.row()) {
            return b.name();
        }
        count++;
    }

    return QVariant();
}


int DataModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0) {
        return 0;
    }
    return m->books.size();

}


bool DataModel::setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole)
{

    if (role != Qt::DisplayRole) {
            return false;
    }

    QList<QVariant> list = value.toList(); // title, description, author, image, category
    auto c = 0;
    auto id = 0;
    for (const auto& b : m->books) {
        if (c == index.row()) {
            id = b.id();
            break;
        }
        c++;
    }

    if (!m->books.contains(id)) {
        return false;
    }
    if (m->books.value(id).name() != list.at(0).toString()) {
        m->books[id].setName(list.at(0).toString());
    }
    if (m->books.value(id).description() != list.at(1).toString()) {
        m->books[id].setDescription(list.at(1).toString());
    }
    if (m->books.value(id).author() != list.at(2).toString()) {
        m->books[id].setAuthor(list.at(2).toString());
    }
    if (m->books.value(id).image() != list.at(3).toString()) {
          m->books[id].setImage(list.at(3).toString());
    }
    if (m->books.value(id).category() != list.at(4).toInt()) {
        m->categories[m->books.value(id).category()].removeBook(m->books.value(id).id());
        m->categories[list.at(4).toInt()].addBook(m->books.value(id).id());
        m->books[id].setCategory(list.at(4).toInt());
    }

    emit (dataChanged(index,index));
    emit (updateBookInfo(index));

    return true;
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const {
    Q_UNUSED(section)

    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Horizontal) {
        return QString("BookList");
    }
    return QVariant();
}


Book DataModel::getBook(const int& row) const {
    auto c = 0;
    for (const auto& b : m->books) {
        if (c == row) {
            return m->books.value(b.id());
        }
        c++;
    }
}

bool DataModel::removeRows(int row, int count, const QModelIndex &parent )
{

    beginRemoveRows(parent, row, row+count-1);
    auto c = 0;
    for (const auto& b : m->books) {
        if (c == row) {
            m->books.remove(b.id());
            m->categories[b.category()].removeBook(b.id());
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
    emit (updateBookInfo(i));
    return true;
}

QString DataModel::getCategoryName(const int& id)
{
    return m->categories.value(id).name();
}

QMap<int, Category>& DataModel::getCategories()
{
    return m->categories;
}


bool DataModel::addBook(QList<QVariant> bookParam) {
    auto id = 0;
    if ( !m->books.empty() ) {
        id = m->books.keys().last();
        id++;
    }

    beginInsertRows(QModelIndex(), m->books.size()-1, m->books.size()-1);
    m->books.insert(id, Book(id, bookParam.at(0).toString(), bookParam.at(1).toString(), bookParam.at(2).toString(), bookParam.at(3).toString(), bookParam.at(4).toInt()));
    m->categories[bookParam.at(4).toInt()].addBook(id);
    endInsertRows();

    return true;
}
