#include "MirrorToolWidget.h"
#include "UserInterface/Common/BmpButton.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QPainter>

class MirrorToolWidgetPrivate
{
    Q_DISABLE_COPY(MirrorToolWidgetPrivate)
public:
    explicit MirrorToolWidgetPrivate(MirrorToolWidget* parent);
    ~MirrorToolWidgetPrivate();
    void initialize();
    void connectAllSlots();
    BmpButton* m_MenuBtn;
    BmpButton* m_CarBtn;
    BmpButton* m_HomeBtn;
    BmpButton* m_BackBtn;
private:
    MirrorToolWidget* m_Parent;
};

MirrorToolWidget::MirrorToolWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new MirrorToolWidgetPrivate(this))
{
}

MirrorToolWidget::~MirrorToolWidget()
{
}

void MirrorToolWidget::resizeEvent(QResizeEvent *event)
{
    int width(40);
    int height(40);
    g_Widget->geometryFit(0, 0, width, g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 40 + (160 - 40) * 0.5, width, height, m_Private->m_MenuBtn);
    g_Widget->geometryFit(0, 140 + (160 - 40) * 0.5, width, height, m_Private->m_HomeBtn);
    g_Widget->geometryFit(0, 240 + (160 - 40) * 0.5, width, height, m_Private->m_BackBtn);
    g_Widget->geometryFit(0, 340 + (160 - 40) * 0.5, width, height, m_Private->m_CarBtn);
    QWidget::resizeEvent(event);
}

void MirrorToolWidget::paintEvent(QPaintEvent *event)
{
#ifdef gcc
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

void MirrorToolWidget::timerEvent(QTimerEvent *event)
{
    QWidget::timerEvent(event);
}

void MirrorToolWidget::onToolBtnRelease()
{
    const BmpButton* ptr = dynamic_cast<const BmpButton*>(sender());
    if (ptr == m_Private->m_CarBtn) {
        emit toolBtnRelease(MirrorToolWidget::T_Car);
    } else if (ptr == m_Private->m_BackBtn) {
        emit toolBtnRelease(MirrorToolWidget::T_Back);
    } else if (ptr == m_Private->m_HomeBtn) {
        emit toolBtnRelease(MirrorToolWidget::T_Home);
    } else if (ptr == m_Private->m_MenuBtn) {
        emit toolBtnRelease(MirrorToolWidget::T_Menu);
    }
}

MirrorToolWidgetPrivate::MirrorToolWidgetPrivate(MirrorToolWidget *parent)
    : m_Parent(parent)
{
    m_CarBtn = NULL;
    m_HomeBtn = NULL;
    m_BackBtn = NULL;
    m_MenuBtn = NULL;
    initialize();
    connectAllSlots();
}

MirrorToolWidgetPrivate::~MirrorToolWidgetPrivate()
{
}

void MirrorToolWidgetPrivate::initialize()
{
    m_CarBtn = new BmpButton(m_Parent);
    m_CarBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MirrorLinkWidgetCarBtnNormal"));
    m_CarBtn->setPressBmpPath(QString(":/Images/Resources/Images/MirrorLinkWidgetCarBtnNormal"));
    m_CarBtn->setVisible(true);
    m_HomeBtn = new BmpButton(m_Parent);
    m_HomeBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MirrorLinkWidgetHomeBtnNormal"));
    m_HomeBtn->setPressBmpPath(QString(":/Images/Resources/Images/MirrorLinkWidgetHomeBtnNormal"));
    m_HomeBtn->setVisible(true);
    m_BackBtn = new BmpButton(m_Parent);
    m_BackBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MirrorLinkWidgetBackBtnNormal"));
    m_BackBtn->setPressBmpPath(QString(":/Images/Resources/Images/MirrorLinkWidgetBackBtnNormal"));
    m_BackBtn->setVisible(true);
    m_MenuBtn = new BmpButton(m_Parent);
    m_MenuBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MirrorLinkWidgetMenuBtnNormal"));
    m_MenuBtn->setPressBmpPath(QString(":/Images/Resources/Images/MirrorLinkWidgetMenuBtnNormal"));
    m_MenuBtn->setVisible(true);
}

void MirrorToolWidgetPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_CarBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolBtnRelease()),
                     type);
    QObject::connect(m_BackBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onToolBtnRelease()),
                     type);
    QObject::connect(m_HomeBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onToolBtnRelease()),
                     type);
    QObject::connect(m_MenuBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onToolBtnRelease()),
                     type);
}
