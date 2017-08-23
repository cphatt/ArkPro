#include "USBDiskListViewWidget.h"
#include "USBDiskMusicListViewWidget/USBDiskMusicListViewWidget.h"
#include "USBDiskImageListViewWidget/USBDiskImageListViewWidget.h"
#include "USBDiskVideoListViewWidget/USBDiskVideoListViewWidget.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "AutoConnect.h"

class USBDiskListViewWidgetPrivate
{
    Q_DISABLE_COPY(USBDiskListViewWidgetPrivate)
public:
    explicit USBDiskListViewWidgetPrivate(USBDiskListViewWidget* parent);
    ~USBDiskListViewWidgetPrivate();
    void initialize();
    void connectAllSlots();
    USBDiskMusicListViewWidget* m_USBDiskMusicListViewWidget;
    USBDiskImageListViewWidget* m_USBDiskImageListViewWidget;
    USBDiskVideoListViewWidget* m_USBDiskVideoListViewWidget;
private:
    USBDiskListViewWidget* m_Parent;
};

USBDiskListViewWidget::USBDiskListViewWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , Multimedia::Interface()
    , m_Private(new USBDiskListViewWidgetPrivate(this))
{
}

USBDiskListViewWidget::~USBDiskListViewWidget()
{
}

void USBDiskListViewWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
}

void USBDiskListViewWidget::resizeEvent(QResizeEvent *event) //USB 列表界面向下偏移 8.7
{
    g_Widget->geometryFit(186, 110, 800 - 186, 365, this);
    QWidget::resizeEvent(event);
}

void USBDiskListViewWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void USBDiskListViewWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    if (WidgetStatus::Show == status) {
        switch (type) {
        case Widget::T_USBDisk:
        case Widget::T_USBDiskMusic:
        case Widget::T_USBDiskImage:
        case Widget::T_USBDiskVideo: {
            setVisible(true);
            break;
        }
        case Widget::T_Music:
        case Widget::T_Image:
        case Widget::T_Video: {
            setVisible(false);
            break;
        }
        default: {
            break;
        }
        }
    }
}

USBDiskListViewWidgetPrivate::USBDiskListViewWidgetPrivate(USBDiskListViewWidget *parent)
    : m_Parent(parent)
{
    m_USBDiskMusicListViewWidget = NULL;
    m_USBDiskImageListViewWidget = NULL;
    m_USBDiskVideoListViewWidget = NULL;
    initialize();
    connectAllSlots();
}

USBDiskListViewWidgetPrivate::~USBDiskListViewWidgetPrivate()
{
}

void USBDiskListViewWidgetPrivate::initialize()
{
    m_USBDiskMusicListViewWidget = new USBDiskMusicListViewWidget(m_Parent);
    m_USBDiskImageListViewWidget = new USBDiskImageListViewWidget(m_Parent);
    m_USBDiskVideoListViewWidget = new USBDiskVideoListViewWidget(m_Parent);
    m_Parent->setVisible(true);
}

void USBDiskListViewWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
}
