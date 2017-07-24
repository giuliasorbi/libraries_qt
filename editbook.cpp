#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMap>
#include <QComboBox>
#include <QMessageBox>
#include <QList>
#include <QFileDialog>
#include <QStandardPaths>
#include "editbook.h"
#include "category.h"


EditBook::EditBook(const QString& name, const QString& desc, const QString& author, const QString& image, const int& category, const QMap<int, Category>& categories, int
                   mode, QWidget* parent)
    : m_name(name),
      m_description(desc),
      m_author(author),
      m_image(image),
      m_category(category),
      m_categories(categories),
      m_mode(mode),
      QWidget(parent)
{
    //create layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *horLayout1 = new QHBoxLayout;
    QLabel* label1 = new QLabel(tr("Title: "));
    m_bookName = new QLineEdit();
    horLayout1->addWidget(label1);
    horLayout1->addWidget(m_bookName);
    QHBoxLayout *horLayout2 = new QHBoxLayout;
    QLabel* label2 = new QLabel(tr("Description: "));
    m_bookDesc = new QTextEdit();
    horLayout2->addWidget(label2);
    horLayout2->addWidget(m_bookDesc);
    QHBoxLayout *horLayout3 = new QHBoxLayout;
    QLabel* label3 = new QLabel(tr("Author: "));
    m_bookAuthor = new QLineEdit();
    horLayout3->addWidget(label3);
    horLayout3->addWidget(m_bookAuthor);
    QHBoxLayout *horLayout4 = new QHBoxLayout;
    QLabel* label4 = new QLabel(tr("Category: "));
    m_bookCat = new QComboBox();
    for (const auto& c : m_categories) {
        m_bookCat->addItem(c.name());
    }
    horLayout4->addWidget(label4);
    horLayout4->addWidget(m_bookCat);
    QHBoxLayout *horLayout5 = new QHBoxLayout;
    QLabel* label5 = new QLabel(tr("Image file:"));
    m_imageName = new QLabel();
    m_btnImage = new QPushButton(tr("Load Image"));
    connect(m_btnImage, SIGNAL(clicked()), this, SLOT(btnImageClicked()));
    horLayout5->addWidget(label5);
    horLayout5->addWidget(m_imageName);
    horLayout5->addWidget(m_btnImage);
    m_bookName->setText(m_name);
    m_bookDesc->setText(m_description);
    m_bookAuthor->setText(m_author);
    m_bookCat->setCurrentIndex(m_bookCat->findData(m_categories.value(m_category).name(), Qt::DisplayRole));
    m_imageName->setText(m_image);
    if (m_image == "") {
        m_btnImage->setText("Load");
    } else {
        m_btnImage->setText("Change");
    }
    m_btnSave = new QPushButton(tr("Save"));
    m_btnSave->setMaximumWidth(200);
    connect(m_btnSave, SIGNAL(clicked()), this, SLOT(btnSaveClicked()));
    mainLayout->addLayout(horLayout1);
    mainLayout->addLayout(horLayout2);
    mainLayout->addLayout(horLayout3);
    mainLayout->addLayout(horLayout4);
    mainLayout->addLayout(horLayout5);
    mainLayout->addWidget(m_btnSave, 0, Qt::AlignCenter);
    setLayout(mainLayout);
    if (m_mode == 0) {
        this->setWindowTitle("Add new book");
    } else {
        this->setWindowTitle("Edit book");
    }
}


void EditBook::btnSaveClicked()
{
    if (m_bookName->text().isEmpty()) {
        QMessageBox box;
        box.setText("Title is empty.");
        box.exec();
    } else {
        emit (bookChanged(m_bookName->text(), m_bookDesc->toPlainText(), m_bookAuthor->text(), m_imageName->text(), m_bookCat->currentIndex(), m_mode));
    }
    this->hide();

}


void EditBook::btnImageClicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open File"), "",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ) );
    QImage* imageObject = new QImage();
    imageObject->load(imagePath);
    QString name = imagePath.right(imagePath.size()-imagePath.lastIndexOf("/")-1);
    imageObject->save(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + name );
    qDebug() << imagePath.lastIndexOf("/") << "\n" ;
    m_imageName->setText(name);
}
