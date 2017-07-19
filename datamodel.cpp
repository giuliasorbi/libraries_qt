#include <QtWidgets>
#include <QMap>
#include "datamodel.h"
#include "datamanager.h"

DataModel::DataModel(/*QMap<int, Category>* cat, */QObject *parent)
    : /*m_categories(cat),*/
      QAbstractItemModel(parent)
{

    m.categories.insert(0, Category(0, "computer science", "computer science category"));
    m.categories.insert(1, Category(1, "action", "action category"));

    QString descr = "The C++11 standard allows programmers\nto express ideas more clearly, simply, and directly,\nand to write faster, more efficient code.\nBjarne Stroustrup, the designer and original implementer of C++,\nthoroughly covers the details of this language and its use\nin his definitive reference,The C++ Programming Language, Fourth Edition.";
    m.books.insert(0, Book(0,"A Tour of C++", descr, "Bjarne Stroustrup", "tour.jpg", 0));

    m.categories[0].addBook(0);
    QString descr1 = "Coming to grips with C++11 and C++14\nis more than a matter of familiarizing yourself with the features they introduce\n(e.g., auto type declarations, move semantics, lambda expressions,\nand concurrency support).\nThe challenge is learning to use those features effectively\n-- so that your software is correct, efficient, maintainable, and portable.";
    m.books.insert(1, Book(1,"Effective Modern c++", descr1, "Scott Meyers", "effectiveModernC++.jpg", 0));
    m.categories[0].addBook(1);
    m.books.insert(2, Book(2,"book2", 1));
    m.categories[1].addBook(2);
    m.books.insert(3, Book(3,"book3", 1));
    m.categories[1].addBook(3);


}


QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole/* && role != Qt::EditRole*/)
        return QVariant();

    if (!index.parent().isValid()) {
        return m.categories.value(index.row()).name();
    }
    else {
        qDebug() << "data" << index.row();
        return m.books.value(index.row()).name();
    }
}

QModelIndex DataModel::index(int row, int column, const QModelIndex &parent) const
{
    if (column > 0) {
        return QModelIndex();
    }
    if (parent.column() > 0) {
        return QModelIndex();
    }

//    qDebug() << "INDEX" << row << column << parent;


    if (!parent.isValid()) {
        qDebug() << "CAT INDEX" << row << column << parent;
        return createIndex(row, 0, 1);
    } else {

        auto i = m.categories.value(parent.row()).books().at(row);
        qDebug() << "BOOK INDEX " << row << column << parent << i;
        return createIndex(i, 0, 2);
    }
}


int DataModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0) {
        return 0;
    }

    qDebug() << "rowCount" << parent;
    if (!parent.isValid()) {
        return m.categories.size();
    } else if (parent.internalId() == 1) {
        return m.categories.value(parent.row()).books().size();
    }

    return 0;
}


QModelIndex DataModel::parent(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return QModelIndex();
    }

    if (index.internalId() == 1) {
        return QModelIndex();
    }

    qDebug() << "parent" << index;
    if (index.internalId() == 2) {
        return createIndex(m.books.value(index.row()).category(), 0, 1);
    }

    return QModelIndex();
}


