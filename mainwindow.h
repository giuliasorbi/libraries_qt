#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QListWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <QPlainTextEdit>
#include <QGroupBox>
#include <QVBoxLayout>

#include "manager.h"
#include "editbook.h"
#include "addcategory.h"
#include "treemodel.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Manager& m, QWidget* parent = nullptr);
    void createToolBars();
    void createActions();
    void createStatusBar();
//    void updateModel();

private:

//    QPlainTextEdit* textEdit;
    QToolBar* libToolBar;
    QAction* newAct;
    QAction* editCatAct;
    QAction* newCat;
    QTreeView *view;
//    QStandardItemModel* model;
    TreeModel* model;
    QGroupBox * groupBox;
    QWidget* ww;

    QPushButton* btnEdit;
    QPushButton* btnDelete;

    QLabel *nameField, *authorField, *descField, *catField, *pix;

    Manager& manager;
    editBook* edit;
    editBook* add;
    addCategory* addCat;

    QModelIndex editBookIndex;


private slots:
    bool showBookInfo();
    void btnEdit_clicked();
    void btnDelete_clicked();
    void newBook();
    void newCategory();

public slots:
    void test(Manager&, const int&);
    void newBookAdded(Manager& m);

};


#endif // MAINWINDOW_H
