#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include "addcategory.h"

addCategory::addCategory(Manager& m, QWidget* parent)
    : manager(m),
      QWidget(parent)

{
    //create layout
    QVBoxLayout *mainLayout = new QVBoxLayout();

    QLabel* labelName = new QLabel(tr("Name: "));
    QLineEdit* catName = new QLineEdit();
    QLabel* labelDesc = new QLabel(tr("Description: "));
    QTextEdit* catDesc = new QTextEdit();

    QPushButton* btnSave = new QPushButton(tr("Save"));
//    connect(btnSave, SIGNAL(clicked()), this, SLOT(btnSave_clicked()));
    mainLayout->addWidget(labelName);
    mainLayout->addWidget(catName);
    mainLayout->addWidget(labelDesc);
    mainLayout->addWidget(catDesc);
    mainLayout->addWidget(btnSave);
    setLayout(mainLayout);
}
// ...
