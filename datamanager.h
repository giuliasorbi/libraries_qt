#ifndef MANAGER_H
#define MANAGER_H

#include <QMap>
#include <QString>
#include "library.h"
#include "category.h"
#include "book.h"


struct DataManager
{
    DataManager();
    QMap<int, Library> libraries;
    QMap<int, Category> categories;
    QMap<int, Book> books;
};

#endif // MANAGER_H
