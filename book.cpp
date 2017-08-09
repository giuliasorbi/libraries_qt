#include "book.h"

Book::Book(){}

Book::Book(int id, QString name, int category)
    : m_id(id),
      m_name(name),
      m_description("book description"),
      m_author("author"),
      m_image(""),
      m_category(category)
{}

Book::Book(int id, QString name, QString desc, QString author, QString image, int category)
    : m_id(id),
      m_name(name),
      m_description(desc),
      m_author(author),
      m_image(image),
      m_category(category)
{}
