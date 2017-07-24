#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QAction>
#include <QIcon>
#include <QListView>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QDebug>
#include <QGroupBox>
#include <QLabel>
#include <QMenuBar>
#include <QToolButton>
#include <QPixmap>
#include <QStandardPaths>
#include <QDir>
#include <QCloseEvent>

#include "mainwindow.h"
#include "book.h"
#include "datamodel.h"
#include "editbook.h"


MainWindow::MainWindow(DataModel* dataModel, CategoriesWindow* catWindow, QWidget *parent)
    : m_dataModel(dataModel),
      m_catWindow(catWindow),
      QMainWindow(parent)

{
    setObjectName("MainWindow");
    createActions();
    createToolBars();
    createStatusBar();
    createLayout();

    QWidget* widget = new QWidget();
    widget->setLayout(m_layout);
    this->setCentralWidget(widget);
    this->setWindowTitle("Books Management");
    this->resize(QSize(600,500));

}

void MainWindow::createActions()
{
    m_newAct = new QAction(QIcon(":img/book1.png"), tr("Add Book"), this);
    m_newAct->setStatusTip(tr("Add new book"));
    connect(m_newAct, SIGNAL(triggered()), this, SLOT(newBook()));

    m_editCatAct = new QAction(QIcon(":img/category.png"), tr("Categories management"), this);
    m_editCatAct->setStatusTip(tr("Categories management"));
    connect(m_editCatAct, SIGNAL(triggered()), this, SLOT(showCategories()));
}

void MainWindow::createToolBars()
{
    QToolBar* libToolBar = addToolBar(tr("Library"));
    libToolBar->addAction(m_newAct);
    libToolBar->addAction(m_editCatAct);
}


void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Click to show book Info"));
}


void MainWindow::createLayout()
{
    m_layout = new QGridLayout();

    m_view = new QListView();
    m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_view->setFixedWidth(250);

    m_view->setModel(m_dataModel);
    connect(m_dataModel, SIGNAL(updateBookInfo(const QModelIndex&)), this , SLOT(showBookInfo(const QModelIndex&)));

    connect(m_view, SIGNAL(clicked(const QModelIndex&)), this, SLOT(showBookInfo(const QModelIndex&)));

    m_layout->addWidget(m_view, 0, 0);

    m_groupBox = new QGroupBox(tr("Book info"));
    QGridLayout* grid = new QGridLayout;
    QVBoxLayout* vbox = new QVBoxLayout;
    QVBoxLayout* vbox2 = new QVBoxLayout;
    QHBoxLayout* buttons = new QHBoxLayout;
    m_nameField = new QLabel();
    QFont titleFont = m_nameField->font();
    titleFont.setPointSize(32);
    titleFont.setBold(true);
    m_nameField->setFont(titleFont);
    QLabel* author = new QLabel();
    QFont labelFont= author->font();
    labelFont.setPointSize(18);
    labelFont.setBold(true);
    author->setFont(labelFont);
    author->setText("Authors:");
    m_authorField = new QLabel();
    QFont fieldFont = m_authorField->font();
    fieldFont.setPointSize(18);
    m_authorField->setFont(fieldFont);
    QLabel* desc = new QLabel();
    desc->setFont(labelFont);
    desc->setText("Description:");
    m_descField = new QLabel();
    m_descField->setFont(fieldFont);
    QLabel* cat = new QLabel();
    cat->setFont(labelFont);
    cat->setText("Category:");
    m_catField = new QLabel();
    m_catField->setFont(fieldFont);
    m_pix = new QLabel();
    QPushButton* btnEdit = new QPushButton(tr("Edit"));
    connect(btnEdit, SIGNAL(clicked()), this, SLOT(btnEditClicked()));
    btnEdit->setMaximumWidth(100);
    QPushButton* btnDelete = new QPushButton(tr("Delete"));
    connect(btnDelete, SIGNAL(clicked()), this, SLOT(btnDeleteClicked()));
    btnDelete->setMaximumWidth(100);
    vbox->addWidget(author);
    vbox->addWidget(m_authorField);
    vbox->addWidget(desc);
    vbox->addWidget(m_descField);
    vbox->addWidget(cat);
    vbox->addWidget(m_catField);
    vbox2->addWidget(m_pix);
    buttons->addWidget(btnEdit);
    buttons->addWidget(btnDelete);
    grid->addWidget(m_nameField, 0, 0, 1, 2, Qt::AlignCenter);
    grid->addLayout(vbox, 1, 0);
    grid->addLayout(vbox2, 1, 1);
    grid->addLayout(buttons, 2, 1);

    m_groupBox->setLayout(grid);
    m_groupBox->setVisible(false);

    m_layout->addWidget(m_groupBox, 0, 1, 1, 1, Qt::AlignCenter);
    m_layout->setColumnStretch(1,1);

}



bool MainWindow::showBookInfo(const QModelIndex& index)
{
    m_editBookIndex = index;
    if (!m_editBookIndex.isValid()) {
        m_view->setCurrentIndex(QModelIndex());
        m_groupBox->setVisible(false);
        return false;
    }

    m_groupBox->setVisible(true);
    m_nameField->setText(m_editBookIndex.data().toString());

    const Book& b = m_dataModel->getBook(m_editBookIndex.row());
//    qDebug() << "BOOK ID " << b.id();

    m_descField->setText(b.description());
    m_authorField->setText(b.author());
    m_catField->setText(m_dataModel->getCategoryName(b.category()));
    if (!QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).exists()) {
        QDir().mkdir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    }
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + '/' + b.image();
    QPixmap image(":/img/book.png");
    if ( (b.image() != "") && (!image.load(path)) ) {
            image.load(":/img/book.png");
    }
    QPixmap scaled = image.scaledToWidth(200);
    m_pix->setPixmap(scaled);

    return true;
}

void MainWindow::btnDeleteClicked()
{
    QModelIndex index = m_view->currentIndex();
    m_dataModel->removeRows(index.row(), 1, index.parent());
}

void MainWindow::btnEditClicked()
{
    const Book& b = m_dataModel->getBook(m_editBookIndex.row());
    const QMap<int, Category>& categories = m_dataModel->getCategories();
    auto mode = 1;
    m_edit = new EditBook(b.name(), b.description(), b.author(), b.image(), b.category(), categories, mode);
    m_edit->show();
    connect(m_edit, SIGNAL(bookChanged(const QString&, const QString&, const QString&, const QString&, const int&, int)), this, SLOT(onBookChanged(const QString&, const QString&, const QString&, const QString&, const int&, int)));
}

void MainWindow::newBook() {
    const QMap<int, Category>& categories = m_dataModel->getCategories();
    auto mode = 0;
    m_edit = new EditBook("", "", "" , "", 0, categories, mode);
    m_edit->show();
    connect(m_edit, SIGNAL(bookChanged(const QString&, const QString&, const QString&, const QString&, const int&, int)), this, SLOT(onBookChanged(const QString&, const QString&, const QString&, const QString&, const int&, int)));
}




bool MainWindow::onBookChanged( const QString& bookName, const QString& bookDesc, const QString& bookAuthor, const QString& bookImage, const int& bookCategory, int mode)
{
    QList<QVariant> list = { bookName, bookDesc, bookAuthor, bookImage, bookCategory };
    qDebug() << "mode onBookChanged " << mode;
    if (mode == 0) {
       return m_dataModel->addBook(list);
    } else {
        return m_dataModel->setData(m_editBookIndex, list, Qt::DisplayRole);
    }
}

void MainWindow::showCategories()
{
    connect(m_catWindow, SIGNAL(close()), this, SLOT(showBookInfo()));
    m_catWindow->init();
    m_catWindow->show();
}


bool MainWindow::showBookInfo(){
    return showBookInfo(m_view->currentIndex());

}
