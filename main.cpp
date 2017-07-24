#include <QApplication>
#include "mainwindow.h"
#include "datamanager.h"
#include "datamodel.h"
#include "catmodel.h"
#include "categorieswindow.h"

void init(DataManager* m){
    m->categories.insert(0, Category(0, "uncategorized books", "uncategorized books"));
    m->categories.insert(1, Category(1, "computer science", "computer science category"));
    m->categories.insert(2, Category(2, "action", "action category"));

    QString descr = "The C++11 standard allows programmers\nto express ideas more clearly, simply, and directly,\nand to write faster, more efficient code.\nBjarne Stroustrup, the designer and original implementer of C++,\nthoroughly covers the details of this language and its use\nin his definitive reference,The C++ Programming Language, Fourth Edition.";
    m->books.insert(0, Book(0, "A Tour of C++", descr, "Bjarne Stroustrup", "tour.jpg", 1));

    m->categories[1].addBook(0);
    QString descr1 = "Coming to grips with C++11 and C++14\nis more than a matter of familiarizing yourself with the features they introduce\n(e.g., auto type declarations, move semantics, lambda expressions,\nand concurrency support).\nThe challenge is learning to use those features effectively\n-- so that your software is correct, efficient, maintainable, and portable.";
    m->books.insert(1, Book(1, "Effective Modern C++", descr1, "Scott Meyers", "effectiveModernC++.jpg", 1));

    m->categories[1].addBook(1);
    m->books.insert(2, Book(2, "book2", 2));
    m->categories[2].addBook(2);
    m->books.insert(3, Book(3, "book3", 2));
    m->categories[2].addBook(3);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataManager m;
    init(&m);
    DataModel dataModel(&m);
    CatModel catModel(&m);
    CategoriesWindow catWindow(&catModel);
    MainWindow w(&dataModel, &catWindow);
    w.show();
    return a.exec();
}

