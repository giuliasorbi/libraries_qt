#ifndef EDITCATEGORY_H
#define EDITCATEGORY_H

#include <QString>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>


class EditCategory : public QWidget
{
    Q_OBJECT
public:
    EditCategory(const QString& name, const QString& description, int mode, QWidget *parent = nullptr);
private:
    QPushButton* m_btnCatSave;
    QLineEdit* m_catName;
    QTextEdit* m_catDesc;
    const QString& m_name;
    const QString& m_description;
    int m_mode;
signals:
    void categoryChanged(const QString&, const QString&, int&);
private slots:
    void btnCatSaveClicked();
};

#endif // EDITCATEGORY_H
