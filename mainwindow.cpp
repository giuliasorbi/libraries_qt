#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QAction>
#include <QIcon>
#include <QTreeView>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QDebug>
#include <QGroupBox>
#include <QLabel>
#include <QMenuBar>
#include <QToolButton>
#include <QPixmap>


#include "mainwindow.h"
#include "category.h"
#include "book.h"
#include "manager.h"
#include "treemodel.h"


MainWindow::MainWindow(Manager& m, QWidget *parent)
    : manager(m),
      QMainWindow(parent)

{
    setObjectName("MainWindow");
    createActions();
    createToolBars();
    createStatusBar();

    QGridLayout *layout = new QGridLayout();

    view = new QTreeView();
    model = new TreeModel();

    // -------------------------------------------------------insert categories and books-------------------------------------------------------
//    qDebug() << "categories size=" << manager.categories.size() << "\n";
//    qDebug() << "books size=" << manager.books.size() << "\n";

    manager.categories.insert(manager.categories.size(), Category(manager.categories.size(), "computer science", "computer science category"));
    manager.categories.insert(manager.categories.size(), Category(manager.categories.size(), "action", "action category"));

//    qDebug() << "categories size=" << manager.categories.size() << "\n";

    manager.categories[0].addBook(manager.books.size());
    QString descr = "The C++11 standard allows programmers\nto express ideas more clearly, simply, and directly,\nand to write faster, more efficient code.\nBjarne Stroustrup, the designer and original implementer of C++,\nthoroughly covers the details of this language and its use\nin his definitive reference,The C++ Programming Language, Fourth Edition.";
    manager.books.insert(manager.books.size(), Book(manager.books.size(),"A Tour of C++", descr, "Bjarne Stroustrup", "tour.jpg", 0));
    manager.categories[0].addBook(manager.books.size());
    QString descr1 = "Coming to grips with C++11 and C++14\nis more than a matter of familiarizing yourself with the features they introduce\n(e.g., auto type declarations, move semantics, lambda expressions,\nand concurrency support).\nThe challenge is learning to use those features effectively\n-- so that your software is correct, efficient, maintainable, and portable.";
    manager.books.insert(manager.books.size(), Book(manager.books.size(),"Effective Modern c++", descr1, "Scott Meyers", "effectiveModernC++.jpg", 0));
    manager.categories[1].addBook(manager.books.size());
    manager.books.insert(manager.books.size(), Book(manager.books.size(),"book2", 1));
    manager.categories[1].addBook(manager.books.size());
    manager.books.insert(manager.books.size(), Book(manager.books.size(),"book3", 1));

 // ------------------------------------------------------------------------------------------------------------------------------------------

 // --------------------- con QStandardItemMOdel----------------------------------------------------------------------------------------------

//    model = new QStandardItemModel;
//    QStandardItem* rootNode = model->invisibleRootItem();
//    int count=0;
//    for(auto c : manager.categories) {
//         QStandardItem* newItem = new QStandardItem(c.name());
//         newItem->setEditable(false);
//         rootNode->appendRow(newItem);
//         for(auto b : c.books()) {
//            QStandardItem* newBookItem = new QStandardItem(manager.books[b].name());
//            qDebug() << "book  " <<  manager.books[b].name() << "\n";
//            newBookItem->setEditable(false);
//            newItem->appendRow(newBookItem);
//         }
//    }
//    model->setHeaderData(0, Qt::Horizontal, "Book List");

// ------------------------------------------------------------------------------------------------------------------------------------------


    for(auto c : manager.categories) {
        auto count = 0;
        model->insertRootChild(c.name());
        QModelIndex index = model->index(c.id(),0,QModelIndex());
//        TreeItem* item = model->getItem(index);
        for(auto b : c.books()) {
//            TreeItem* item = model->getItem(index);
//            item->insertChildren(item->childCount(), 1);
//            item->child(item->childCount() - 1)->setData(manager.books[b].name());
            model->insertRow(/*item->childCount()*/ count, index);
            QModelIndex child = model->index(/*item->childCount()*/ count, 0, index);

            model->setData(child, QVariant(manager.books[b].name()), Qt::DisplayRole);
        count++;
        }
    }


    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setModel(model);
    view->expandAll();

    connect(view, SIGNAL(clicked(QModelIndex)), this, SLOT(showBookInfo()));
    layout->addWidget(view,0,0);

    groupBox = new QGroupBox(tr("Book info"));
    QGridLayout* grid = new QGridLayout;

    QVBoxLayout* vbox = new QVBoxLayout;
    QVBoxLayout* vbox2 = new QVBoxLayout;
    QHBoxLayout* buttons = new QHBoxLayout;

    nameField = new QLabel();
    QFont titleFont = nameField->font();
    titleFont.setPointSize(32);
    titleFont.setBold(true);
    nameField->setFont(titleFont);
    QLabel* author = new QLabel();
    QFont labelFont= author->font();
    labelFont.setPointSize(18);
    labelFont.setBold(true);
    author->setFont(labelFont);
    author->setText("Authors:");
    authorField = new QLabel();
    QFont fieldFont = authorField->font();
    fieldFont.setPointSize(18);
    authorField->setFont(fieldFont);
    QLabel* desc = new QLabel();
    desc->setFont(labelFont);
    desc->setText("Description:");
    descField = new QLabel();
    descField->setFont(fieldFont);

    QLabel* cat = new QLabel();
    cat->setFont(labelFont);
    cat->setText("Category:");

    catField = new QLabel();
    catField->setFont(fieldFont);
    pix = new QLabel();

    btnEdit = new QPushButton(tr("Edit"));
    connect(btnEdit, SIGNAL(clicked()), this, SLOT(btnEdit_clicked()));
    btnEdit->setMaximumWidth(100);

    btnDelete = new QPushButton(tr("Delete"));
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(btnDelete_clicked()));
    btnDelete->setMaximumWidth(100);


//    vbox->addWidget(nameField);
    vbox->addWidget(author);
    vbox->addWidget(authorField);
    vbox->addWidget(desc);
    vbox->addWidget(descField);
    vbox->addWidget(cat);
    vbox->addWidget(catField);
    vbox2->addWidget(pix);
    buttons->addWidget(btnEdit);
    buttons->addWidget(btnDelete);
    buttons->addStretch(1);

    grid->addWidget(nameField,0,0,1,2,Qt::AlignCenter);
    grid->addLayout(vbox, 1,0);
    grid->addLayout(vbox2, 1,1);
    grid->addLayout(buttons,2,1);
    grid->setColumnStretch(0,1);
    grid->setColumnStretch(1,1);


    groupBox->setLayout(grid);
    groupBox->setVisible(false);

    layout->addWidget(groupBox,0,1);

    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,2);
    layout->setColumnMinimumWidth(0,200);

    QWidget* widget = new QWidget();
    widget->setLayout(layout);
    this->setCentralWidget(widget);
}


void MainWindow::createToolBars()
{
    libToolBar = addToolBar(tr("Library"));
    libToolBar->addAction(newAct);
    libToolBar->addAction(editCatAct);
    editCatAct->setIconVisibleInMenu(false);
    QToolButton *catButton = dynamic_cast<QToolButton*>(libToolBar->widgetForAction(editCatAct));
    catButton->setPopupMode(QToolButton::InstantPopup);
    catButton->addAction(newCat);


}

void MainWindow::createActions()
{
    newAct = new QAction(QIcon(":img/book1.png"), tr("New"), this);
    newAct->setStatusTip(tr("Add new book"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newBook()));

    editCatAct = new QAction(QIcon(":img/category.png"), tr("Edit"), this);
    editCatAct ->setStatusTip(tr("Manage categories"));
//    connect(editCatAct, SIGNAL(triggered()), this, SLOT(editCategory()));

    newCat = new QAction(tr("Add"), this);
    newCat->setStatusTip(tr("Add new category"));
    connect(newCat, SIGNAL(triggered()), this, SLOT(newCategory()));

}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Click to show book Info"));
}

bool MainWindow::showBookInfo()
{
    QModelIndex index = view->currentIndex();

    if(index.parent() == QModelIndex()) {
        qDebug() << "selectd category\n";
        return false;
    }
    groupBox->setVisible(true);

    int currentRow = index.row();

    QModelIndex parentIndex = index.parent();

    QString category = view->model()->data(parentIndex).toString();
    int parentRow = parentIndex.row();
    QString a = manager.books[manager.categories[parentRow].books().at(currentRow)].author();
    QString d =  manager.books[manager.categories[parentRow].books().at(currentRow)].description();
    QString bookName = manager.books[manager.categories[parentRow].books().at(currentRow)].name();

    nameField->setText(bookName);
    authorField->setText(a);
    descField->setText(d);
    catField->setText(category);
    QPixmap image(":/img/book.png");
    if( (manager.books[manager.categories[parentRow].books().at(currentRow)].image() != "") &&
       ( !image.load("/Users/dev/workspace/libraries_qt/img/"+manager.books[manager.categories[parentRow].books().at(currentRow)].image())) ) {
            image.load(":/img/book.png");
        }
    QPixmap scaled = image.scaledToWidth(200);
    pix->setPixmap(scaled);

    return true;
}


void MainWindow::btnEdit_clicked()
{

    editBookIndex = view->currentIndex();
    qDebug() << "row of selected item " << editBookIndex.row() << "\n";
    qDebug() << "category of selected item " << editBookIndex.parent().row() << "\n";
    int bookId = manager.categories[editBookIndex.parent().row()].books().at(editBookIndex.row());
    qDebug() << "books size " << manager.categories[editBookIndex.parent().row()].books().size() << "\n";

    edit = new editBook(manager, bookId, 1); // Manager, bookId, mode = 1
    edit->show();
    connect(edit, SIGNAL(signal_test(Manager&, const int&)), this, SLOT(test(Manager&, const int&) ));

}


void MainWindow::test(Manager& m, const int& bookId) {
    this->show();
    manager = m;

    int currentRow = editBookIndex.row();
    int rowParent = editBookIndex.parent().row();

    if(manager.books[bookId].category()!= rowParent) {

        model->removeRows(currentRow, 1, editBookIndex.parent());

        QModelIndex index = model->index((manager.books[bookId].category()),0,QModelIndex());
        TreeItem* item = model->getItem(index);
        int row = item->childCount();
        model->insertRow(row, index);

        QModelIndex child = model->index(row, 0, index);

        model->setData(child, QVariant(manager.books[bookId].name()), Qt::DisplayRole);
        manager.categories[manager.books[bookId].category()].addBook(bookId);
        qDebug() << "rowParent" << rowParent<< "bookId" << bookId << "\n";
        qDebug() << manager.categories[rowParent].books().size() << "\n";

        manager.categories[rowParent].removeBook(currentRow);

    }
    else {
        model->setData(editBookIndex, QVariant(manager.books[bookId].name()));
    }

    showBookInfo();

}

void MainWindow::newBook() {

    add = new editBook(manager, 0, 0); // Manager, id, mode
    add->show();
    connect(add, SIGNAL(signal_addBook(Manager&)), this, SLOT(newBookAdded(Manager&) ));

}

void MainWindow::newBookAdded(Manager& m)
{
//    this->show();
    manager = m;
    auto newId = manager.books.keys().last();
    qDebug() << "newId " << newId << "\n";


    int cat = manager.books[newId].category();
    qDebug() << "new book category " << cat;
    QModelIndex index = model->index(cat,0,QModelIndex());
    TreeItem* item = model->getItem(index);
    int row = item->childCount();
    model->insertRow(row, index);
    QModelIndex child = model->index(row, 0, index);
    model->setData(child, QVariant(manager.books[newId].name()), Qt::DisplayRole);
    manager.categories[cat].addBook(newId);

}


void MainWindow::btnDelete_clicked()
{
    editBookIndex = view->currentIndex();
    int categoryId = editBookIndex.parent().row();
    model->removeRows(editBookIndex.row(), 1, editBookIndex.parent());
    int bookId = manager.categories[categoryId].books().at(editBookIndex.row());
    manager.categories[categoryId].removeBook(editBookIndex.row());
    manager.books.remove(bookId);
    showBookInfo();
}

void MainWindow::newCategory()
{
    addCat = new addCategory(manager);
    addCat->show();
    qDebug() <<"HERE\n";
}


