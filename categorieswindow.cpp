#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QListView>
#include <QStandardItemModel>
#include <QDebug>
#include <QLabel>
#include <QStandardItemModel>
#include <QPushButton>
#include <QStatusBar>

#include "categorieswindow.h"

CategoriesWindow::CategoriesWindow(CatModel* catModel, QWidget *parent)
    : m_catModel(catModel),
      QMainWindow(parent)

{
    setObjectName("CategoriesWindow");
    QWidget* widget = new QWidget();
    m_layout = new QGridLayout();
    QVBoxLayout* vbox = new QVBoxLayout;
    m_btnNewCategory = new QPushButton(tr("Add Category"));
    m_btnNewCategory->setMaximumWidth(150);
    connect(m_btnNewCategory, SIGNAL(clicked()), this, SLOT(btnNewCategoryClicked()));
    m_listView = new QListView();
    connect(m_listView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(showCatInfo(const QModelIndex&)));
    m_listView->setModel(m_catModel);
    connect(m_catModel, SIGNAL(updateCatInfo(const QModelIndex &)), this , SLOT(showCatInfo(const QModelIndex&)));
    vbox->addWidget(m_btnNewCategory);
    m_listView->setFixedWidth(250);
    vbox->addWidget(m_listView);
    m_layout->addWidget(m_btnNewCategory, 0, 0, 1, 1, Qt::AlignCenter);
    m_layout->addWidget(m_listView, 1, 0);
    m_info = new QWidget();
    QVBoxLayout* vbox1 = new QVBoxLayout;
    m_catName = new QLabel();
    QFont titleFont = m_catName->font();
    titleFont.setPointSize(32);
    titleFont.setBold(true);
    m_catName->setFont(titleFont);
    QLabel* descriptionLabel = new QLabel();
    QFont labelFont = descriptionLabel->font();
    labelFont.setPointSize(18);
    labelFont.setBold(true);
    descriptionLabel->setFont(labelFont);
    descriptionLabel->setText("Category description:");
    m_catDesc = new QLabel();
    QFont fieldFont = m_catDesc->font();
    fieldFont.setPointSize(18);
    m_catDesc->setFont(fieldFont);
    QLabel* booksLabel = new QLabel();
    booksLabel->setFont(labelFont);
    booksLabel->setText("BookList:");
    QListView* bookListView = new QListView();
    bookListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_bookListModel = new QStandardItemModel();
    bookListView->setModel(m_bookListModel);
    QHBoxLayout* buttons = new QHBoxLayout;
    m_btnCatEdit = new QPushButton(tr("Edit Category"));
    connect(m_btnCatEdit, SIGNAL(clicked()), this, SLOT(btnCatEditClicked()));
    m_btnCatEdit->setMaximumWidth(150);
    m_btnCatDelete = new QPushButton(tr("Delete Category"));
    connect(m_btnCatDelete, SIGNAL(clicked()), this, SLOT(btnCatDeleteClicked()));
    m_btnCatDelete->setMaximumWidth(150);
    buttons->addWidget(m_btnCatEdit);
    buttons->addWidget(m_btnCatDelete);
    vbox1->addWidget(m_catName);
    vbox1->addWidget(descriptionLabel);
    vbox1->addWidget(m_catDesc);
    vbox1->addWidget(booksLabel);
    vbox1->addWidget(bookListView);
    vbox1->addLayout(buttons);
    m_info->setLayout(vbox1);
    m_layout->addWidget(m_info, 0, 1, 2, 1, Qt::AlignJustify);
    m_layout->setColumnStretch(1,1);
    widget->setLayout(m_layout);
    this->setCentralWidget(widget);
    this->setWindowTitle("Categories Management");
    this->statusBar()->showMessage(tr("Click to show category Info"));
}

bool CategoriesWindow::showCatInfo(const QModelIndex& index) {
    if (!index.isValid()) {
        m_info->setVisible(false);
        return false;
    }
    if (index.row() == 0) {
        m_btnCatDelete->setEnabled(false);
        m_btnCatEdit->setEnabled(false);
    } else {
        m_btnCatDelete->setEnabled(true);
        m_btnCatEdit->setEnabled(true);
    }

    m_info->setVisible(true);
    m_catName->setText(index.data().toString());
    m_catDesc->setText(m_catModel->getCategoryDesc(index.row()));
    m_bookListModel->clear();
    auto row = 0;
    for (const auto& c : m_catModel->getBookList(index.row())){
        QStandardItem *item = new QStandardItem(c);
        m_bookListModel->setItem(row, 0, item);
        item->setFlags(Qt::ItemIsEnabled);
        row++;
    }
    return true;
}

void CategoriesWindow::btnCatDeleteClicked()
{
    QModelIndex index = m_listView->currentIndex();
    m_catModel->removeRows(index.row(), 1, index.parent());
}

void CategoriesWindow::btnCatEditClicked()
{
    m_editCatIndex = m_listView->currentIndex();
    m_editCat = new EditCategory(m_catName->text(), m_catDesc->text(), 1);
    m_editCat->show();
    connect(m_editCat, SIGNAL(categoryChanged(const QString&, const QString&, int&)), this, SLOT(onCategoryChanged(const QString&, const QString&, int&)));
}

void CategoriesWindow::btnNewCategoryClicked() {
    m_editCat = new EditCategory("", "", 0);
    m_editCat->show();
    connect(m_editCat, SIGNAL(categoryChanged(const QString&, const QString&, int&)), this, SLOT(onCategoryChanged(const QString&, const QString&, int&)));
}


bool CategoriesWindow::onCategoryChanged(const QString& catName , const QString& catDesc, int& mode)
{
    QList<QVariant> list = { catName, catDesc };
    if (mode == 0) {
        return m_catModel->addCategory(list);
    } else {
        return m_catModel->setData(m_editCatIndex, list, Qt::DisplayRole);
    }

}

void CategoriesWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
    emit (close());
}

void CategoriesWindow::init()
{
    m_listView->setCurrentIndex(QModelIndex());
    this->resize(500,300);
    m_info->setVisible(false);
}




