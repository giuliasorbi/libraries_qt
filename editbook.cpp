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
#include "editbook.h"


editBook::editBook(Manager& m, int id, int mode, QWidget* parent) // [mode = 0 --> add new book , mode = 1 --> edit book]
    : manager(m),
      m_bookId(id),
      m_mode(mode),
      QWidget(parent)
{
    //create layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *horLayout1 = new QHBoxLayout;

    QLabel* label1 = new QLabel(tr("Title: "));
    bookName = new QLineEdit();
    horLayout1->addWidget(label1);
    horLayout1->addWidget(bookName);

    QHBoxLayout *horLayout2 = new QHBoxLayout;

    QLabel* label2 = new QLabel(tr("Description: "));
    bookDesc = new QTextEdit();
    horLayout2->addWidget(label2);
    horLayout2->addWidget(bookDesc);

    QHBoxLayout *horLayout3 = new QHBoxLayout;

    QLabel* label3 = new QLabel(tr("Author: "));
    bookAuthor = new QLineEdit();

    horLayout3->addWidget(label3);
    horLayout3->addWidget(bookAuthor);

    QHBoxLayout *horLayout4 = new QHBoxLayout;

    QLabel* label4 = new QLabel(tr("Category: "));

    bookCat = new QComboBox();

    for(auto c : manager.categories) {
        bookCat->addItem(c.name());
    }

    horLayout4->addWidget(label4);
    horLayout4->addWidget(bookCat);

    QHBoxLayout *horLayout5 = new QHBoxLayout;

    QLabel* label5 = new QLabel(tr("Image file:"));
    imageName = new QLabel();
    btnImage = new QPushButton(tr("Load Image"));
    connect(btnImage, SIGNAL(clicked()), this, SLOT(btnImage_clicked()));

    horLayout5->addWidget(label5);
    horLayout5->addWidget(imageName);
    horLayout5->addWidget(btnImage);

    if(m_mode == 1) {
        bookName->setText(manager.books[m_bookId].name());
        bookDesc->setText(manager.books[m_bookId].description());
        bookAuthor->setText(manager.books[m_bookId].author());
        bookCat->setCurrentIndex(bookCat->findData(manager.categories[manager.books[m_bookId].category()].name(), Qt::DisplayRole));
        imageName->setText(manager.books[m_bookId].image());
        btnImage->setText("Change");
    }

    btnSave = new QPushButton(tr("Save"));
    connect(btnSave, SIGNAL(clicked()), this, SLOT(btnSave_clicked()));
    mainLayout->addLayout(horLayout1);
    mainLayout->addLayout(horLayout2);
    mainLayout->addLayout(horLayout3);
    mainLayout->addLayout(horLayout4);
    mainLayout->addLayout(horLayout5);
    mainLayout->addWidget(btnSave);

    setLayout(mainLayout);
    qDebug() << "id recv " << m_bookId;

}


void editBook::btnSave_clicked()
{
    if(bookName->text().isEmpty()) {
        QMessageBox box;
        box.setText("Title is empty.");
        box.exec();
    }
    else {

        if(m_mode == 0) { // new book
            qDebug() << "NEW BOOK\n";
            auto id = manager.books.keys().last();
            id++;
            qDebug() << "new book id " << id << "\n";
            manager.books.insert(id, Book(id, bookName->text(), bookDesc->toPlainText(), bookAuthor->text(), imageName->text(), bookCat->currentIndex()));
            emit(signal_addBook(manager));
            this->hide();

        }
        else { // edit book
            qDebug() << "EDIT BOOK\n";

            manager.books[m_bookId].set_name(bookName->text());
            manager.books[m_bookId].set_description(bookDesc->toPlainText());
            manager.books[m_bookId].set_author(bookAuthor->text());
            int ind = bookCat->currentIndex();
            manager.books[m_bookId].set_category(ind);
            manager.books[m_bookId].set_image(imageName->text());
            qDebug()<< bookDesc->toPlainText() << " " << ind;
            emit(signal_test(manager, m_bookId));
            this->hide();

        }

    }


}


void editBook::btnImage_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open File"), "",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ) );
    QImage* imageObject = new QImage();
    imageObject->load(imagePath);
    qDebug() << imagePath << "\n";
    QString name = imagePath.right(imagePath.size()-imagePath.lastIndexOf("/")-1);
    qDebug() << name << "\n";

    imageObject->save("/Users/dev/workspace/libraries_qt/img/"+name);
    qDebug() << imagePath.lastIndexOf("/") << "\n" ;
    imageName->setText(name);

//    QPixmap image = QPixmap::fromImage(*imageObject);
}

//void editBook::closeEvent(QCloseEvent* event)
//{
//    qDebug() << "close\n";
//    emit(signal_close());
//}

