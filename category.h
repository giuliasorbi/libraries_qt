#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include <QVector>


class Category
{
public:
    Category();
    Category(int id, QString name, QString description);
//    void set_name(QString name) { m_name = name; }
//    void set_description(QString description) { m_description = description; }
    QString name() const { return m_name; }
    QString description() const { return m_description; }
    int id() const {return m_id; }
    QVector<int> books() const { return m_books; }

    void removeBook(const int& bookId) { m_books.remove(bookId); }
    void addBook(const int& bookId) { m_books.append(bookId); }

    void showBooks() const;

private:
    int m_id;
    QString m_name;
    QString m_description;
    QVector<int> m_books;
};

#endif // CATEGORY_H
