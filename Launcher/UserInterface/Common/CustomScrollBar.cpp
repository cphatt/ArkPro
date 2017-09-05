#include "CustomScrollBar.h"

class CustomScrollBarPrivate
{
public:
    explicit CustomScrollBarPrivate(CustomScrollBar* parent);
    ~CustomScrollBarPrivate();
private:
    CustomScrollBar* m_Parent;
};

CustomScrollBar::CustomScrollBar(QWidget *parent)
    : QScrollBar(parent)
    , m_Private(new CustomScrollBarPrivate(this))
{
}

CustomScrollBar::~CustomScrollBar()
{
}

CustomScrollBarPrivate::CustomScrollBarPrivate(CustomScrollBar *parent)
    : m_Parent(parent)
{
}

CustomScrollBarPrivate::~CustomScrollBarPrivate()
{
}
