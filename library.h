#ifndef LIBRARY_H
#define LIBRARY_H

#include <QString>
#include <QMap>
//#include "category.h"

class Library
{
public:
    Library(QString name );
    void set_name(QString name) { m_name = name; }
//    void set_categories( QMap<int, category> categories ) { m_categories = categories; }

    QString name()const { return m_name; }
//    int id() const {return m_id; }
//    QMap<int, category> categories() { return m_categories; }

private:
    QString m_name;

//    QMap<int, category> m_categories; // <category id, Category>
};

#endif // LIBRARY_H
