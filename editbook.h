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
#include "book.h"
#include "category.h"


class EditBook : public QWidget
{
    Q_OBJECT
public:
    EditBook(const QString& name, const QString& desc, const QString& author, const QString& image, const int& category, const QMap<int, Category>& categories, int mode, QWidget *parent = nullptr);
private:
    QPushButton* m_btnSave;
    QPushButton* m_btnImage;
    QLineEdit* m_bookName;
    QLineEdit* m_bookAuthor;
    QComboBox* m_bookCat;
    QTextEdit* m_bookDesc;
    QLabel* m_imageName;
    const QString& m_name;
    const QString& m_description;
    const QString& m_author;
    const QString& m_image;
    const int& m_category;
    int m_mode;
    const QMap<int, Category>& m_categories;
signals:
    void bookChanged(const QString&, const QString&, const QString&, const QString&, const int&, int);
private slots:
    void btnSaveClicked();
    void btnImageClicked();
};


#endif // EDITBOOK_H
