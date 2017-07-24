#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QList>
#include <QMenuBar>

#include "editcategory.h"

EditCategory::EditCategory(const QString& name, const QString& description, int mode, QWidget* parent) // mode 0 --> new category, mode 1 --> edit category
    : m_name(name),
      m_description(description),
      m_mode(mode),
      QWidget(parent)

{
    qDebug() << "mode " << m_mode;
    //create layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *horLayout1 = new QHBoxLayout;

    QLabel* label1 = new QLabel(tr("Name: "));
    m_catName = new QLineEdit();
    horLayout1->addWidget(label1);
    horLayout1->addWidget(m_catName);

    QHBoxLayout *horLayout2 = new QHBoxLayout;

    QLabel* label2 = new QLabel(tr("Description: "));
    m_catDesc = new QTextEdit();
    horLayout2->addWidget(label2);
    horLayout2->addWidget(m_catDesc);
    m_catName->setText(m_name);
    m_catDesc->setText(m_description);

    m_btnCatSave = new QPushButton(tr("Save"));
    connect(m_btnCatSave, SIGNAL(clicked()), this, SLOT(btnCatSaveClicked()));
    m_btnCatSave->setMaximumWidth(200);
    mainLayout->addLayout(horLayout1);
    mainLayout->addLayout(horLayout2);
    mainLayout->addWidget(m_btnCatSave, 0, Qt::AlignCenter);
    setLayout(mainLayout);
    this->setWindowTitle("Add new Category");
}


void EditCategory::btnCatSaveClicked()
{
    if (m_catName->text().isEmpty()) {
        QMessageBox box;
        box.setText("Name is empty.");
        box.exec();
    } else {
        emit(categoryChanged(m_catName->text(), m_catDesc->toPlainText(), m_mode));
    }
    this->hide();
}
