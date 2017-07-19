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
#include "datamanager.h"
//#include "treemodel.h"
#include "datamodel.h"


MainWindow::MainWindow( QWidget *parent)
    : QMainWindow(parent)

{
    setObjectName("MainWindow");
    createActions();
    createToolBars();
    createStatusBar();

    QGridLayout *layout = new QGridLayout();

    view = new QTreeView();
//    model = new TreeModel();
    dataModel = new DataModel();

    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setModel(dataModel);
    view->expandAll();

    layout->addWidget(view,0,0);
    QWidget* widget = new QWidget();
    widget->setLayout(layout);
    this->setCentralWidget(widget);
//    this->setLayout(layout);


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
//    connect(newAct, SIGNAL(triggered()), this, SLOT(newBook()));

    editCatAct = new QAction(QIcon(":img/category.png"), tr("Edit"), this);
    editCatAct ->setStatusTip(tr("Manage categories"));
//    connect(editCatAct, SIGNAL(triggered()), this, SLOT(editCategory()));

    newCat = new QAction(tr("Add"), this);
    newCat->setStatusTip(tr("Add new category"));
//    connect(newCat, SIGNAL(triggered()), this, SLOT(newCategory()));

}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Click to show book Info"));
}
