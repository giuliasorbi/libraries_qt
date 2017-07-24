#ifndef CATEGORIESWINDOW_H
#define CATEGORIESWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QMap>
#include <QStandardItemModel>
#include <QListView>

#include "category.h"
#include "catmodel.h"
#include "editcategory.h"
class CategoriesWindow : public QMainWindow
{

    Q_OBJECT

public:
    CategoriesWindow(CatModel* catModel, QWidget* parent = nullptr);
    void init();
private:
    QGridLayout* m_layout;
    QWidget* m_info;
    QLabel *m_catName, *m_catDesc;
    CatModel* m_catModel;
    QStandardItemModel* m_bookListModel;
    QListView* m_listView;
    QModelIndex m_editCatIndex;
    EditCategory* m_editCat;
    QPushButton *m_btnCatDelete, *m_btnCatEdit, *m_btnNewCategory;
    void closeEvent(QCloseEvent *event);
signals:
    void close();
private slots:
    bool showCatInfo(const QModelIndex& index);
    void btnCatDeleteClicked();
    void btnCatEditClicked();
    void btnNewCategoryClicked();
public slots:
    bool onCategoryChanged(const QString&, const QString&, int&);

};

#endif // CATEGORIESWINDOW_H
