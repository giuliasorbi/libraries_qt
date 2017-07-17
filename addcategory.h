#ifndef ADDCATEGORY_H
#define ADDCATEGORY_H

#include <QWidget>
#include "manager.h"


class addCategory : public QWidget
{
    Q_OBJECT

public:
    addCategory(Manager& m, QWidget *parent = nullptr);

private:
    Manager& manager;
};

#endif // ADDCATEGORY_H
