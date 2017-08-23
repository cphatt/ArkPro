#include "ImageStatusWidget.h"
#include "UserInterface/Common/TextWidget.h"
#include "UserInterface/Common/Utility.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "AutoConnect.h"
#include "EventEngine.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QPainter>
#include <QDebug>
#include <QVariant>
#include <QFileInfo>

namespace SourceString {
static const QString Image = QString(QObject::tr("Image>"));
}

class ImageStatusWidgetPrivate
{
    Q_DISABLE_COPY(ImageStatusWidgetPrivate)
public:
    explicit ImageStatusWidgetPrivate(ImageStatusWidget* parent);
    ~ImageStatusWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    TextWidget* m_TitleText;
    TextWidget* m_FileNameText;
private:
    ImageStatusWidget* m_Parent;
};

ImageStatusWidget::ImageStatusWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , Multimedia::Interface()
    , m_Private(new ImageStatusWidgetPrivate(this))
{
}

ImageStatusWidget::~ImageStatusWidget()
{
}

void ImageStatusWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), 58, this);
    g_Widget->geometryFit(0, 0, 172, 58, m_Private->m_TitleText);
    g_Widget->geometryFit(172, 0, 800, 58, m_Private->m_FileNameText);
    QWidget::resizeEvent(event);
}

void ImageStatusWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(Utility::multimediaAlphaColor()));
    QWidget::paintEvent(event);
}

void ImageStatusWidget::customEvent(QEvent *event)
{
    qDebug()  << "ImageStatusWidget::customEvent" << event->type();
    switch (event->type()) {
    case CustomEventType::ImageStatusWidgetAddChild: {
        EventEngine::CustomEvent<QVariant>* ptr = dynamic_cast<EventEngine::CustomEvent<QVariant>*>(event);
        if ((NULL != ptr)
                && (ptr->m_Data)
                && (ptr->m_Data->canConvert<QWidget*>())
                && (ptr->m_Data->value<QWidget*>())) {
            ptr->m_Data->value<QWidget*>()->setParent(this);
            ptr->m_Data->value<QWidget*>()->setVisible(true);
        }
        break;
    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void ImageStatusWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    if (WidgetStatus::Show == status) {
        switch (type) {
        case Widget::T_Image: {
            setVisible(true);
            break;
        }
        default: {
            setVisible(false);
            break;
        }
        }
    }
}

void ImageStatusWidget::onImagePlayerChange(const DeviceWatcherType type, const QString &filePath, const int index, const int percent, const int rotate)
{
    QFileInfo fileInfo(filePath);
    m_Private->m_FileNameText->setText(fileInfo.fileName());
}

ImageStatusWidgetPrivate::ImageStatusWidgetPrivate(ImageStatusWidget *parent)
    : m_Parent(parent)
{
    m_TitleText = NULL;
    m_FileNameText = NULL;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

ImageStatusWidgetPrivate::~ImageStatusWidgetPrivate()
{
}

void ImageStatusWidgetPrivate::initialize()
{
    m_TitleText = new TextWidget(m_Parent);
    m_TitleText->setAlignmentFlag(Qt::AlignRight | Qt::AlignVCenter);
    int fontPointSize(19 * g_Widget->widthScalabilityFactor());
    m_TitleText->setFontPointSize(fontPointSize);
    m_TitleText->setText(SourceString::Image);
    m_TitleText->show();
    m_FileNameText = new TextWidget(m_Parent);
    m_FileNameText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    m_FileNameText->setFontPointSize(fontPointSize);
    m_FileNameText->setLanguageType(TextWidget::T_NoTranslate);
    m_FileNameText->show();
    m_Parent->setVisible(false);
}

void ImageStatusWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void ImageStatusWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
}
