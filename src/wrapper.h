#ifndef WRAPPER_H
#define WRAPPER_H

#include <QWidget>

#include "core.h"

class Wrapper :
    public QWidget
{
    Q_OBJECT

public:
    Wrapper(QWidget *parent = nullptr);
};

#endif // WRAPPER_H
