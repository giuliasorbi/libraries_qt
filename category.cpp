#include <QString>
#include <QDebug>
#include "category.h"
#include "datamanager.h"

Category::Category(){};

Category::Category( int id, QString name, QString description )
    : m_id(id),
      m_name(name),
      m_description(description),
      m_books()
{}

