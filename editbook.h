#ifndef EDITBOOK_H
#define EDITBOOK_H
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMap>
#include <QTextEdit>
#include <QComboBox>
#include <QCloseEvent>
#include <QList>
#include <QLabel>
#include "manager.h"


class editBook : public QWidget
{
    Q_OBJECT
public:
    editBook(Manager& m, int id, int mode, QWidget *parent = nullptr);

private:
//    void closeEvent(QCloseEvent* event);
    QPushButton* btnSave;
    QPushButton* btnImage;
    QLineEdit* bookName;
    QLineEdit* bookAuthor;
    QComboBox* bookCat;
    QTextEdit* bookDesc;
    QLabel* imageName;
    Manager& manager;
    int m_bookId;
    int m_mode;

signals:
    void signal_test(Manager&, const int&);
    void signal_addBook(Manager&);
//    void signal_close();

private slots:
    void btnSave_clicked();
    void btnImage_clicked();
};


#endif // EDITBOOK_H
