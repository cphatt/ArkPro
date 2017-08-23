#include "MultimediaListView.h"
#include "UserInterface/Common/CustomItemDelegate.h"
#include "UserInterface/Common/CustomScrollBar.h"
#include "BusinessLogic/Widget/Widget.h"
#include "UserInterface/Common/Utility.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMetaType>
#include <QDebug>
#include <QPainter>

class MultimediaVariant
{
public:
    MultimediaVariant();
    ~MultimediaVariant();
    QString m_Text;
};
Q_DECLARE_METATYPE(MultimediaVariant)

class MultimediaDelegate : public CustomItemDelegate
{
    Q_DISABLE_COPY(MultimediaDelegate)
public:
    explicit MultimediaDelegate(QWidget* widget = NULL);
    ~MultimediaDelegate();
protected:
    void mousePressEvent(QMouseEvent* event,
                         QAbstractItemModel *model,
                         const QStyleOptionViewItem &option,
                         const QModelIndex &index);
    void mouseMoveEvent(QMouseEvent* event,
                        QAbstractItemModel *model,
                        const QStyleOptionViewItem &option,
                        const QModelIndex &index);
    void mouseReleaseEvent(QMouseEvent* event,
                           QAbstractItemModel *model,
                           const QStyleOptionViewItem &option,
                           const QModelIndex &index);
    void paint(QPainter* painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
};

class MultimediaListViewPrivate
{
    Q_DISABLE_COPY(MultimediaListViewPrivate)
public:
    explicit MultimediaListViewPrivate(MultimediaListView* parent);
    ~MultimediaListViewPrivate();
    void initialize();
    QStandardItemModel* m_StandardItemModel;
    MultimediaDelegate* m_MultimediaDelegate;
    CustomScrollBar* m_CustomScrollBar;
private:
    MultimediaListView* m_Parent;
};

MultimediaListView::MultimediaListView(QWidget *parent)
    : CustomListView(parent)
    , m_Private(new MultimediaListViewPrivate(this))
{
}

MultimediaListView::~MultimediaListView()
{
}

void MultimediaListView::clearListView()
{
    m_Private->m_StandardItemModel->clear();
}

void MultimediaListView::appendListView(QString path)  //媒体列表中单个数据设置
{
    QStandardItem* root = m_Private->m_StandardItemModel->invisibleRootItem();
    QStandardItem* item = new QStandardItem();
    item->setSizeHint(QSize((1174 - 278)  * g_Widget->widthScalabilityFactor(), 63 * g_Widget->heightScalabilityFactor()));
    MultimediaVariant variant;
    variant.m_Text = path;
    item->setData(qVariantFromValue(variant), Qt::DisplayRole);
    root->setChild(root->rowCount(), 0, item);
}

MultimediaListViewPrivate::MultimediaListViewPrivate(MultimediaListView *parent)
    : m_Parent(parent)
{
    m_StandardItemModel = NULL;
    m_MultimediaDelegate = NULL;
    m_CustomScrollBar = NULL;
    initialize();
}

MultimediaListViewPrivate::~MultimediaListViewPrivate()
{
}

void MultimediaListViewPrivate::initialize()
{
    m_CustomScrollBar = new CustomScrollBar(m_Parent);
    int width = 14 * g_Widget->widthScalabilityFactor();
    m_CustomScrollBar->setStyleSheet("QScrollBar:vertical{"
                                     "width:" + QString::number(width) + "px;"
                                                                         "background:rgba(0, 94, 187, 255);"
                                                                         "margin:0px, 0px, 0px, 0px;"
                                                                         "padding-top:0px;"
                                                                         "padding-bottom:0px;"
                                                                         "}"
                                                                         "QScrollBar::handle:vertical{"
                                                                         "width:" + QString::number(width) + "px;"
                                                                                                             "background:rgba(158, 158, 47, 255);"
                                                                                                             "}"
                                                                                                             "QScrollBar::handle:vertical:pressed{"
                                                                                                             "width:" + QString::number(width) + "px;"
                                                                                                                                                 "background:rgba(158, 158, 47, 255);"
                                                                                                                                                 "}"
                                                                                                                                                 "QScrollBar::handle:vertical:disabled{"
                                                                                                                                                 "width:" + QString::number(width) + "px;"
                                                                                                                                                                                     "background:rgba(0, 94, 187, 255);"
                                                                                                                                                                                     "}"
                                                                                                                                                                                     "QScrollBar::add-line:vertical{"
                                                                                                                                                                                     "height:0px;"
                                                                                                                                                                                     "subcontrol-position:bottom;"
                                                                                                                                                                                     "}"
                                                                                                                                                                                     "QScrollBar::sub-line:vertical{"
                                                                                                                                                                                     "height:0px;"
                                                                                                                                                                                     "subcontrol-position:top;"
                                                                                                                                                                                     "}"
                                                                                                                                                                                     "QScrollBar::add-page:vertical{"
                                                                                                                                                                                     "background:rgba(0, 94, 187, 255);"
                                                                                                                                                                                     "}"
                                                                                                                                                                                     "QScrollBar::sub-page:vertical{"
                                                                                                                                                                                     "background:rgba(0, 94, 187, 255);"
                                                                                                                                                                                     "}");
    m_StandardItemModel = new QStandardItemModel(m_Parent);
    m_MultimediaDelegate = new MultimediaDelegate(m_Parent);
    m_Parent->setVerticalScrollBar(m_CustomScrollBar);
    m_Parent->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_Parent->setItemDelegate(m_MultimediaDelegate);
    m_Parent->setModel(m_StandardItemModel);
}

MultimediaVariant::MultimediaVariant()
{
    m_Text.clear();
}

MultimediaVariant::~MultimediaVariant()
{
}

MultimediaDelegate::MultimediaDelegate(QWidget *widget)
    : CustomItemDelegate(widget)
{

}

MultimediaDelegate::~MultimediaDelegate()
{

}

void MultimediaDelegate::mousePressEvent(QMouseEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
}

void MultimediaDelegate::mouseMoveEvent(QMouseEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
}

void MultimediaDelegate::mouseReleaseEvent(QMouseEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
}

void MultimediaDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    qDebug() << "MultimediaDelegate::paint" << option.rect << option.rect.adjusted(0, 0, -17 * g_Widget->widthScalabilityFactor(), 0);
    painter->fillRect(option.rect.adjusted(0, 0, -17 * g_Widget->widthScalabilityFactor(), 0), Utility::listViewItemBrush());
    MultimediaVariant variant = qVariantValue<MultimediaVariant>(index.data(Qt::DisplayRole));
    QFont font;
    font.setPointSize(20 *g_Widget->widthScalabilityFactor());
    painter->setFont(font);
    painter->setPen(Qt::white);
    QString text;
    text = QObject::tr(variant.m_Text.toLocal8Bit().constData());
    painter->drawText(option.rect.adjusted(75 * g_Widget->widthScalabilityFactor(), 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, QString::number(index.row() + 1) + QString(".") + text);
    painter->setPen(Utility::customBlackColor());
    painter->drawLine(QPoint(0, option.rect.y() + option.rect.height() - 1), QPoint(option.rect.width() - 17 * g_Widget->widthScalabilityFactor(), option.rect.y() + option.rect.height() - 1));
    painter->restore();
}
