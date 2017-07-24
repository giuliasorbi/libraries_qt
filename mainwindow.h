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
#include <QLabel>

#include "datamanager.h"
#include "editbook.h"
#include "datamodel.h"
//#include "addbook.h"
#include "categorieswindow.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DataModel* dataModel, CategoriesWindow* CategoriesWindow, QWidget* parent = nullptr);
    void createToolBars();
    void createActions();
    void createStatusBar();
    void createLayout();
private:
    QAction* m_newAct;
    QAction* m_editCatAct;
    QListView* m_view;
    QGridLayout* m_layout;
    QGroupBox* m_groupBox;
    QLabel *m_nameField, *m_authorField, *m_descField, *m_catField, *m_pix;
    EditBook* m_edit;
    QModelIndex m_editBookIndex;
    DataModel* m_dataModel;
    CategoriesWindow* m_catWindow;
private slots:
    bool showBookInfo(const QModelIndex&);
    bool showBookInfo();
    void btnEditClicked();
    void btnDeleteClicked();
    void newBook();
    void showCategories();
public slots:
    bool onBookChanged(const QString&, const QString&, const QString&, const QString&, const int&, int);
};


#endif // MAINWINDOW_H
