#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QVector>

class Book
{
public:
    Book();
    Book(int id, QString name, QString desc, QString author, QString image, int category);
    Book(int id, QString name, int category);
    QString name() const { return m_name; }
    QString author() const { return m_author; }
    QString description() const { return m_description; }
    QString image() const { return m_image; }
    int category() const { return m_category; }
    void set_name(const QString& name) { m_name = name; }
    void set_author(const QString& a) { m_author=a; }
    void set_description(const QString& desc) { m_description = desc; }
    void set_category(const int& cat) {m_category = cat; }
    void set_image(const QString& image) { m_image = image; }


private:
    int m_id;
    QString m_name;
    QString m_description;
    QString m_author;
    QString m_image;
    int m_category;

};

#endif // BOOK_H

