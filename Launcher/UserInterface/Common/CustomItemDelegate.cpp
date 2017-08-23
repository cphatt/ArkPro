#include "CustomItemDelegate.h"
#include <QPainter>
#include <QDebug>
#include <QEvent>

class CustomItemDelegatePrivate
{
    Q_DISABLE_COPY(CustomItemDelegatePrivate)
public:
    explicit CustomItemDelegatePrivate(CustomItemDelegate* parent);
    ~CustomItemDelegatePrivate();
private:
    CustomItemDelegate* m_Parent;
};

CustomItemDelegate::CustomItemDelegate(QWidget *parent)
    : QItemDelegate(parent)
    , m_Private(new CustomItemDelegatePrivate(this))
{
}

CustomItemDelegate::~CustomItemDelegate()
{
}

void CustomItemDelegate::mousePressEvent(QMouseEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
}

void CustomItemDelegate::mouseMoveEvent(QMouseEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
}

void CustomItemDelegate::mouseReleaseEvent(QMouseEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
}

bool CustomItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress: {
        QMouseEvent* mouseEvent = reinterpret_cast<QMouseEvent*>(event);
        if (NULL != mouseEvent) {
            mousePressEvent(mouseEvent, model, option, index);
        }
        break;
    }
    case QEvent::MouseMove: {
        QMouseEvent* mouseEvent = reinterpret_cast<QMouseEvent*>(event);
        if (NULL != mouseEvent) {
            mouseMoveEvent(mouseEvent, model, option, index);
        }
        break;
    }
    case QEvent::MouseButtonRelease: {
        QMouseEvent* mouseEvent = reinterpret_cast<QMouseEvent*>(event);
        if (NULL != mouseEvent) {
            mouseReleaseEvent(mouseEvent, model, option, index);
        }
        break;
    }
    default: {
        break;
    }
    }
    return QItemDelegate::editorEvent(event, model, option, index);
}

QWidget *CustomItemDelegate::createEditor(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QItemDelegate::createEditor(editor, option, index);
}

void CustomItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QItemDelegate::updateEditorGeometry(editor, option, index);
}

QSize CustomItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QItemDelegate::sizeHint(option, index);
}

void CustomItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QItemDelegate::setEditorData(editor, index);
}

void CustomItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QItemDelegate::setModelData(editor, model, index);
}

void CustomItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QItemDelegate::paint(painter, option, index);
}

CustomItemDelegatePrivate::CustomItemDelegatePrivate(CustomItemDelegate *parent)
    : m_Parent(parent)
{
}

CustomItemDelegatePrivate::~CustomItemDelegatePrivate()
{
}
