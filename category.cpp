#include <QString>
#include <QDebug>
#include "category.h"
#include "manager.h"

Category::Category(){};

Category::Category( int id, QString name, QString description )
    : m_id(id),
      m_name(name),
      m_description(description),
      m_books({})
{}

void Category::showBooks() const
{
    for( auto book : m_books ) {
      qDebug() << book << "\n";

    }
}

