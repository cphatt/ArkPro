#include "ImageToolBarWidget.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/Utility.h"
#include "AutoConnect.h"
#include <QPainter>
#include <QDebug>

class ImageToolBarWidgetPrivate
{
    Q_DISABLE_COPY(ImageToolBarWidgetPrivate)
public:
    explicit ImageToolBarWidgetPrivate(ImageToolBarWidget* parent);
    ~ImageToolBarWidgetPrivate();
    void initialize();
    void connectSlots();
    BmpButton* m_RotateBtn;
    BmpButton* m_PreviousBtn;
    BmpButton* m_ToggleBtn;
    BmpButton* m_NextBtn;
    BmpButton* m_ZoomInBtn;
    BmpButton* m_ZoomOutBtn;
private:
    ImageToolBarWidget* m_Parent;
};

ImageToolBarWidget::ImageToolBarWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new ImageToolBarWidgetPrivate(this))
{
}

ImageToolBarWidget::~ImageToolBarWidget()
{
}

void ImageToolBarWidget::resizeEvent(QResizeEvent *event)
{
//    g_Widget->geometryFit(0, 80, g_Widget->baseWindowWidth(), 80, this);
    setGeometry(0, 480 - 82 , 800 , 82);
    int width(82);
    int height(82);
//    g_Widget->geometryFit(0, (123 - height) * 0.5, width, height, m_Private->m_RotateBtn);
//    g_Widget->geometryFit(310 + (353 - 310 - width) / 2, (123 - height) * 0.5, width, height, m_Private->m_PreviousBtn);
//    g_Widget->geometryFit(507 + (557 - 507 - width) / 2, (123 - height) * 0.5, width, height, m_Private->m_ToggleBtn);
//    g_Widget->geometryFit(705 + (748 - 705 - width) / 2, (123 - height) * 0.5, width, height, m_Private->m_NextBtn);
//    g_Widget->geometryFit(892 + (962 - 892 - width) / 2, (123 - height) * 0.5, width, height, m_Private->m_ZoomInBtn);
//    g_Widget->geometryFit(1093 + (1163 - 1093 - width) / 2, (123 - height) * 0.5, width, height, m_Private->m_ZoomOutBtn);
    g_Widget->geometryFit( 27, 0, width, height, m_Private->m_RotateBtn);
    g_Widget->geometryFit(153, 0, width, height, m_Private->m_PreviousBtn);
    g_Widget->geometryFit(287, 0, width, height, m_Private->m_ToggleBtn);
    g_Widget->geometryFit(419, 0, width, height, m_Private->m_NextBtn);
    g_Widget->geometryFit(550, 0, width, height, m_Private->m_ZoomInBtn);
    g_Widget->geometryFit(683, 0, width, height, m_Private->m_ZoomOutBtn);
//    QWidget::resizeEvent(event);
}

void ImageToolBarWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(Utility::multimediaAlphaColor()));
    QWidget::paintEvent(event);
}

void ImageToolBarWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
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

void ImageToolBarWidget::onImagePlayerPlayStatus(const ImagePlayerPlayStatus status)
{
    qDebug () << "ImageToolBarWidget::onImagePlayerPlayStatus" << status;
    switch (status) {
        case IPPS_Browse: {
            m_Private->m_ToggleBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetPauseBtnNormal"));
            m_Private->m_ToggleBtn->setPressBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetPauseBtnNormal"));
            break;
        }
        case IPPS_Pause: {
            m_Private->m_ToggleBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetPlayBtnNormal"));
            m_Private->m_ToggleBtn->setPressBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetPlayBtnNormal"));
            break;
        }
        default: {
            break;
        }
    }
}

void ImageToolBarWidget::onToolButtonRelease()
{
    if (sender() == m_Private->m_RotateBtn) {
        g_Multimedia->imagePlayerRotateImage();
    } else if (sender() == m_Private->m_PreviousBtn) {
        g_Multimedia->imagePlayerPlayPreviousListViewIndex();
    } else if (sender() == m_Private->m_ToggleBtn) {
        g_Multimedia->imagePlayerSetPlayStatusToggle();
    } else if (sender() == m_Private->m_NextBtn) {
        g_Multimedia->imagePlayerPlayNextListViewIndex();
    } else if (sender() == m_Private->m_ZoomInBtn) {
        g_Multimedia->imagePlayerZoomInImage();
    } else if (sender() == m_Private->m_ZoomOutBtn) {
        g_Multimedia->imagePlayerZoomOutImage();
    }
}

ImageToolBarWidgetPrivate::ImageToolBarWidgetPrivate(ImageToolBarWidget *parent)
    : m_Parent(parent)
{
    m_RotateBtn = NULL;
    m_PreviousBtn = NULL;
    m_ToggleBtn = NULL;
    m_NextBtn = NULL;
    m_ZoomInBtn = NULL;
    m_ZoomOutBtn = NULL;
    initialize();
    connectSlots();
    m_Parent->setVisible(false);
}

ImageToolBarWidgetPrivate::~ImageToolBarWidgetPrivate()
{
}

void ImageToolBarWidgetPrivate::initialize()
{
    m_RotateBtn = new BmpButton(m_Parent);
    m_RotateBtn->setNormalBmpPath(QString(":/Images/Resources/Images/ImageToolBarWidgetRotateNormal"));
    m_RotateBtn->setPressBmpPath(QString(":/Images/Resources/Images/ImageToolBarWidgetRotatePress"));
    m_RotateBtn->show();
    m_PreviousBtn = new BmpButton(m_Parent);
    m_PreviousBtn->setNormalBmpPath(QString(":/Images/Resources/Images/ImageToolBarWidgetPreviousNormal"));
    m_PreviousBtn->setPressBmpPath(QString(":/Images/Resources/Images/ImageToolBarWidgetPreviousPress"));
    m_PreviousBtn->show();
    m_ToggleBtn = new BmpButton(m_Parent);
    m_ToggleBtn->setNormalBmpPath(QString(":/Images/Resources/Images/ImageToolBarWidgetPlayNormal"));
    m_ToggleBtn->setPressBmpPath(QString(":/Images/Resources/Images/ImageToolBarWidgetPlayPress"));
    m_ToggleBtn->show();
    m_NextBtn = new BmpButton(m_Parent);
    m_NextBtn->setNormalBmpPath(QString(":/Images/Resources/Images/ImageToolBarWidgetNextNormal"));
    m_NextBtn->setPressBmpPath(QString(":/Images/Resources/Images/ImageToolBarWidgetNextPress"));
    m_NextBtn->show();
    m_ZoomInBtn = new BmpButton(m_Parent);
    m_ZoomInBtn->setNormalBmpPath(QString(":/Images/Resources/Images/ImageToolBarWidgetZoomInNormal"));
    m_ZoomInBtn->setPressBmpPath(QString(":/Images/Resources/Images/ImageToolBarWidgetZoomInPress"));
    m_ZoomInBtn->show();
    m_ZoomOutBtn = new BmpButton(m_Parent);
    m_ZoomOutBtn->setNormalBmpPath(QString(":/Images/Resources/Images/ImageToolBarWidgetZoomOutNormal"));
    m_ZoomOutBtn->setPressBmpPath(QString(":/Images/Resources/Images/ImageToolBarWidgetZoomOutPress"));
    m_ZoomOutBtn->show();
}

void ImageToolBarWidgetPrivate::connectSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_RotateBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_PreviousBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,   SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_ToggleBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_NextBtn,   SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_ZoomInBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_ZoomOutBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onToolButtonRelease()),
                     type);
}
