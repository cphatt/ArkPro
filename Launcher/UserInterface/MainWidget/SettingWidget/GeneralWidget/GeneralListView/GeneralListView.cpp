#include "GeneralListView.h"
#include "UserInterface/Common/CustomItemDelegate.h"
#include "UserInterface/Common/Utility.h"
#include "GeneralSlider/GeneralSlider.h"
#include "BusinessLogic/Widget/Widget.h"
#include "AutoConnect.h"
#include "UserInterface/Common/CustomScrollBar.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QDebug>
#include <QPainter>
#include <QMetaType>
#include <QEvent>

namespace SourceString {
static const QString Brightness = QString(QObject::tr("Brightness"));
static const QString Contrast = QString(QObject::tr("Contrast"));
static const QString Hue = QString(QObject::tr("Hue"));
static const QString Volume = QString(QObject::tr("Volume"));
static const QString Calibrate = QString(QObject::tr("Calibrate"));
static const QString Reset = QString(QObject::tr("Reset"));
}

class GeneralVariant
{
public:
    GeneralVariant();
    ~GeneralVariant();
    QWidget* m_Slider;
    QString m_Text;
    QString m_Value;
};
Q_DECLARE_METATYPE(GeneralVariant)
class GeneralDelegate : public CustomItemDelegate
{
    Q_DISABLE_COPY(GeneralDelegate)
public:
    explicit GeneralDelegate(QWidget *parent = NULL);
    ~GeneralDelegate();
protected:
    void paint(QPainter* painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;
};

class GeneralListViewPrivate
{
    Q_DISABLE_COPY(GeneralListViewPrivate)
public:
    explicit GeneralListViewPrivate(GeneralListView* parent);
    ~GeneralListViewPrivate();
    void initialize();
    void connectAllSlots();
    QStandardItemModel* m_StandardItemModel;
    GeneralDelegate* m_GeneralDelegate;
    CustomScrollBar* m_CustomScrollBar;
    GeneralSlider* m_BrightnessSlider;
    GeneralSlider* m_ConstrastSlider;
    GeneralSlider* m_HueSlider;
    GeneralSlider* m_VolumeSlider;
private:
    GeneralListView* m_Parent;
};


GeneralListView::GeneralListView(QWidget *parent)
    : CustomListView(parent)
    , Setting::Interface()
    , Audio::Interface()
    , m_Private(new GeneralListViewPrivate(this))
{
}

GeneralListView::~GeneralListView()
{

}

void GeneralListView::changeEvent(QEvent *event)
{
    switch (event->type()) {
    case QEvent::LanguageChange: {
        break;
    }
    default: {
        break;
    }
    }
    CustomListView::changeEvent(event);
}

void GeneralListView::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, 625, 355, this);
    CustomListView::resizeEvent(event);
}

void GeneralListView::paintEvent(QPaintEvent *event)
{
    QListView::paintEvent(event);
}

void GeneralListView::onMinusBtnRelease()
{
    qDebug() << "GeneralListView::onMinusBtnRelease";
    if (sender() == m_Private->m_BrightnessSlider) {
        qDebug() << "m_BrightnessSlider";
        g_Setting->setBrightness(ST_Minus, 1);
    } else if (sender() == m_Private->m_ConstrastSlider) {
        qDebug() << "m_ConstrastSlider";
        g_Setting->setContrast(ST_Minus, 1);
    } else if (sender() == m_Private->m_HueSlider) {
        qDebug() << "m_Hue";
        g_Setting->setHue(ST_Minus, 1);
    } else if (sender() == m_Private->m_VolumeSlider) {
        qDebug() << "m_VolumeSlider";
        g_Audio->requestDecreaseVolume();
    }
}

void GeneralListView::onPlusBtnRelease()
{
    qDebug() << "GeneralWidget::onPlusBtnRelease";
    if (sender() == m_Private->m_BrightnessSlider) {
        qDebug() << "m_BrightnessSlider";
        g_Setting->setBrightness(ST_Plus, 1);
    } else if (sender() == m_Private->m_ConstrastSlider) {
        qDebug() << "m_ConstrastSlider";
        g_Setting->setContrast(ST_Plus, 1);
    } else if (sender() == m_Private->m_HueSlider) {
        qDebug() << "m_Hue";
        g_Setting->setHue(ST_Plus, 1);
    } else if (sender() == m_Private->m_VolumeSlider) {
        qDebug() << "m_VolumeSlider";
        g_Audio->requestIncreaseVolume();
    }
}

void GeneralListView::onTickMarksMillesimalEnd(const int millesimal)
{
    int value = millesimal * (7 - (-7)) / 1000;
    qDebug() << "GeneralWidget::onTickMarksMillesimalEnd" << millesimal << value;
    if (sender() == m_Private->m_BrightnessSlider) {
        qDebug() << "m_BrightnessSlider";
        g_Setting->setBrightness(ST_Value, value);
    } else if (sender() == m_Private->m_ConstrastSlider) {
        qDebug() << "m_ConstrastSlider";
    } else if (sender() == m_Private->m_HueSlider) {
        qDebug() << "m_Hue";
    } else if (sender() == m_Private->m_VolumeSlider) {
        qDebug() << "m_VolumeSlider";
    }
}

void GeneralListView::onDateTimeChange(const QString &date, const QString &time)
{

}

void GeneralListView::onLanguageTranslateChange(const int language)
{

}

void GeneralListView::onBrightnessChange(const int value)
{
    qDebug() << "GeneralWidget::onBrightnessChange" << value << 1000 * value / (7 - (-7));
    m_Private->m_BrightnessSlider->setTickMarksMillesimal(1000 * value / (7 - (-7)));
    QModelIndex modelIndex = m_Private->m_StandardItemModel->index(0, 0, QModelIndex());
    GeneralVariant variant = qVariantValue<GeneralVariant>(modelIndex.data());
    variant.m_Value = QString::number(value - 7);
    m_Private->m_StandardItemModel->setData(modelIndex, qVariantFromValue(variant), Qt::DisplayRole);
}

void GeneralListView::onContrastChange(const int value)
{
    qDebug() << "GeneralWidget::onContrastChange" << value << 1000 * value / (7 - (-7));
    m_Private->m_ConstrastSlider->setTickMarksMillesimal(1000 * value / (7 - (-7)));
    QModelIndex modelIndex = m_Private->m_StandardItemModel->index(1, 0, QModelIndex());
    GeneralVariant variant = qVariantValue<GeneralVariant>(modelIndex.data());
    variant.m_Value = QString::number(value - 7);
    m_Private->m_StandardItemModel->setData(modelIndex, qVariantFromValue(variant), Qt::DisplayRole);
}

void GeneralListView::onHueChange(const int value)
{
    qDebug() << "GeneralListView::onHueChange" << value << 1000 * value / (7 - (-7));
    m_Private->m_HueSlider->setTickMarksMillesimal(1000 * value / (7 - (-7)));
    QModelIndex modelIndex = m_Private->m_StandardItemModel->index(2, 0, QModelIndex());
    GeneralVariant variant = qVariantValue<GeneralVariant>(modelIndex.data());
    variant.m_Value = QString::number(value - 7);
    m_Private->m_StandardItemModel->setData(modelIndex, qVariantFromValue(variant), Qt::DisplayRole);
}

void GeneralListView::onFMChange(int freq)
{
}

void GeneralListView::onFMIsOpen(int open)
{
}

void GeneralListView::onVolumeChange(int volume)
{
    m_Private->m_VolumeSlider->setTickMarksMillesimal(1000 * volume / (40 - (-0)));
    QModelIndex modelIndex = m_Private->m_StandardItemModel->index(3, 0, QModelIndex());
    GeneralVariant variant = qVariantValue<GeneralVariant>(modelIndex.data());
    variant.m_Value = QString::number(volume);
    m_Private->m_StandardItemModel->setData(modelIndex, qVariantFromValue(variant), Qt::DisplayRole);
}

void GeneralListView::onVolumeRangeChange(int min, int max)
{

}

GeneralListViewPrivate::GeneralListViewPrivate(GeneralListView *parent)
    : m_Parent(parent)
{
    m_BrightnessSlider = NULL;
    m_HueSlider = NULL;
    m_ConstrastSlider = NULL;
    m_VolumeSlider = NULL;
    m_StandardItemModel = NULL;
    m_GeneralDelegate = NULL;
    m_CustomScrollBar = NULL;
    initialize();
    connectAllSlots();
    m_Parent->setVisible(true);
}

GeneralListViewPrivate::~GeneralListViewPrivate()
{
}

void GeneralListViewPrivate::initialize()
{
    m_CustomScrollBar = new CustomScrollBar(m_Parent);
    int width = 14 * g_Widget->widthScalabilityFactor();
    m_CustomScrollBar->setStyleSheet(QString("QScrollBar:vertical{"
                                             "width:" + QString::number(width) + "px;"
                                                                                 "background:rgba(255, 255, 255, 255);"
                                                                                 "margin:0px, 0px, 0px, 0px;"
                                                                                 "padding-top:0px;"
                                                                                 "padding-bottom:0px;"
                                                                                 "}"
                                                                                 "QScrollBar::handle:vertical:disabled{"
                                                                                 "width:" + QString::number(width) + "px;"
                                                                                                                     "background:rgba(0, 94, 187, 255);"
                                                                                                                     "}"
                                                                                                                     "QScrollBar::add-line:vertical{"
                                                                                                                     "height:0px;"
                                                                                                                     "}"
                                                                                                                     "QScrollBar::sub-line:vertical{"
                                                                                                                     "height:0px;"
                                                                                                                     "}"
                                             ));
    m_Parent->setVerticalScrollBar(m_CustomScrollBar);
    m_Parent->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_BrightnessSlider = new GeneralSlider(m_Parent);
    m_BrightnessSlider->hide();
    m_BrightnessSlider->setMinimumValue(-7);
    m_BrightnessSlider->setMaximumValue(7);
    m_ConstrastSlider = new GeneralSlider(m_Parent);
    m_ConstrastSlider->hide();
    m_ConstrastSlider->setMinimumValue(-7);
    m_ConstrastSlider->setMaximumValue(7);
    m_HueSlider = new GeneralSlider(m_Parent);
    m_HueSlider->hide();
    m_HueSlider->setMinimumValue(-7);
    m_HueSlider->setMaximumValue(7);
    m_VolumeSlider = new GeneralSlider(m_Parent);
    m_VolumeSlider->hide();
    m_VolumeSlider->setMinimumValue(0);
    m_VolumeSlider->setMaximumValue(40);
    m_StandardItemModel = new QStandardItemModel(m_Parent);
    m_GeneralDelegate = new GeneralDelegate(m_Parent);
    m_Parent->setItemDelegate(m_GeneralDelegate);
    QStandardItem* brightnessItem = new QStandardItem();
    GeneralVariant variant;
    variant.m_Text = SourceString::Brightness;
    variant.m_Value = QString("0");
    variant.m_Slider = m_BrightnessSlider;
    brightnessItem->setSizeHint(QSize((1174 - 278)  * g_Widget->widthScalabilityFactor(), 92 * g_Widget->heightScalabilityFactor()));
    brightnessItem->setData(qVariantFromValue(variant), Qt::DisplayRole);
    QStandardItem* contrastItem = new QStandardItem();
    variant.m_Text = SourceString::Contrast;
    variant.m_Value = QString("0");
    variant.m_Slider = m_ConstrastSlider;
    contrastItem->setSizeHint(QSize((1174 - 278)  * g_Widget->widthScalabilityFactor(), 92 * g_Widget->heightScalabilityFactor()));
    contrastItem->setData(qVariantFromValue(variant), Qt::DisplayRole);
    QStandardItem* hueItem = new QStandardItem();
    variant.m_Text = SourceString::Hue;
    variant.m_Value = QString("0");
    variant.m_Slider = m_HueSlider;
    hueItem->setSizeHint(QSize((1174 - 278)  * g_Widget->widthScalabilityFactor(), 92 * g_Widget->heightScalabilityFactor()));
    hueItem->setData(qVariantFromValue(variant), Qt::DisplayRole);
    QStandardItem* volumeItem = new QStandardItem();
    variant.m_Text = SourceString::Volume;
    variant.m_Value = QString("20");
    variant.m_Slider = m_VolumeSlider;
    volumeItem->setSizeHint(QSize(1174 - 278, 92 * g_Widget->heightScalabilityFactor()));
    volumeItem->setData(qVariantFromValue(variant), Qt::DisplayRole);
    QStandardItem* calibrateItem = new QStandardItem();
    variant.m_Text = SourceString::Calibrate;
    variant.m_Value.clear();
    variant.m_Slider = NULL;
    calibrateItem->setSizeHint(QSize((1174 - 278) * g_Widget->widthScalabilityFactor(), 92 * g_Widget->heightScalabilityFactor()));
    calibrateItem->setData(qVariantFromValue(variant), Qt::DisplayRole);
    QStandardItem* resetItem = new QStandardItem();
    variant.m_Text = SourceString::Reset;
    variant.m_Value.clear();
    variant.m_Slider = NULL;
    resetItem->setSizeHint(QSize((1174 - 278) * g_Widget->widthScalabilityFactor(), 92 * g_Widget->heightScalabilityFactor()));
    resetItem->setData(qVariantFromValue(variant), Qt::DisplayRole);
    QStandardItem* root = m_StandardItemModel->invisibleRootItem();
    root->setChild(0, 0, brightnessItem);
    root->setChild(1, 0, contrastItem);
    root->setChild(2, 0, hueItem);
    root->setChild(3, 0, volumeItem);
    root->setChild(4, 0, calibrateItem);
    root->setChild(5, 0, resetItem);
    m_Parent->setModel(m_StandardItemModel);
}

void GeneralListViewPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Setting, m_Parent);
    connectSignalAndSlotByNamesake(g_Audio, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_BrightnessSlider, SIGNAL(minusBtnRelease()),
                     m_Parent,           SLOT(onMinusBtnRelease()),
                     type);
    QObject::connect(m_BrightnessSlider, SIGNAL(plusBtnRelease()),
                     m_Parent,           SLOT(onPlusBtnRelease()),
                     type);
    QObject::connect(m_BrightnessSlider, SIGNAL(tickMarksMillesimalEnd(const int)),
                     m_Parent,           SLOT(onTickMarksMillesimalEnd(const int)),
                     type);
    QObject::connect(m_ConstrastSlider, SIGNAL(minusBtnRelease()),
                     m_Parent,          SLOT(onMinusBtnRelease()),
                     type);
    QObject::connect(m_ConstrastSlider, SIGNAL(plusBtnRelease()),
                     m_Parent,          SLOT(onPlusBtnRelease()),
                     type);
    QObject::connect(m_ConstrastSlider, SIGNAL(tickMarksMillesimalEnd(const int)),
                     m_Parent,          SLOT(onTickMarksMillesimalEnd(const int)),
                     type);
    QObject::connect(m_HueSlider, SIGNAL(minusBtnRelease()),
                     m_Parent,    SLOT(onMinusBtnRelease()),
                     type);
    QObject::connect(m_HueSlider, SIGNAL(plusBtnRelease()),
                     m_Parent,    SLOT(onPlusBtnRelease()),
                     type);
    QObject::connect(m_HueSlider, SIGNAL(tickMarksMillesimalEnd(const int)),
                     m_Parent,    SLOT(onTickMarksMillesimalEnd(const int)),
                     type);
    QObject::connect(m_VolumeSlider, SIGNAL(minusBtnRelease()),
                     m_Parent,       SLOT(onMinusBtnRelease()),
                     type);
    QObject::connect(m_VolumeSlider, SIGNAL(plusBtnRelease()),
                     m_Parent,       SLOT(onPlusBtnRelease()),
                     type);
    QObject::connect(m_VolumeSlider, SIGNAL(tickMarksMillesimalEnd(const int)),
                     m_Parent,       SLOT(onTickMarksMillesimalEnd(const int)),
                     type);
}

GeneralVariant::GeneralVariant()
{
    m_Slider = NULL;
    m_Text.clear();
    m_Value.clear();
}

GeneralVariant::~GeneralVariant()
{
}

GeneralDelegate::GeneralDelegate(QWidget *parent)
{
}

GeneralDelegate::~GeneralDelegate()
{
}

void GeneralDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    qDebug() << "GeneralDelegate::paint" << option.rect << option.rect.adjusted(0, 0, -17 * g_Widget->widthScalabilityFactor(), 0);
    painter->fillRect(option.rect.adjusted(0, 0, -17 * g_Widget->widthScalabilityFactor(), 0), Utility::listViewItemBrush());
    GeneralVariant variant = qVariantValue<GeneralVariant>(index.data(Qt::DisplayRole));
    QFont font;
    font.setPointSize(20 *g_Widget->widthScalabilityFactor());
    painter->setFont(font);
    painter->setPen(Qt::white);
    QString text;
    text = QObject::tr(variant.m_Text.toLocal8Bit().constData());
    if (!variant.m_Value.isEmpty()) {
        text += QString(" ") + variant.m_Value;
    }
    if (NULL != variant.m_Slider) {
        QRect rect(option.rect.x() + (537 - 277) * g_Widget->widthScalabilityFactor(), option.rect.y(), (1071 - 537) * g_Widget->widthScalabilityFactor(), option.rect.height());
        variant.m_Slider->setGeometry(rect);
        variant.m_Slider->setVisible(true);
    }
    painter->drawText(option.rect.adjusted(75 * g_Widget->widthScalabilityFactor(), 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
    painter->setPen(Utility::customBlackColor());
    painter->drawLine(QPoint(0, option.rect.y() + option.rect.height() - 1), QPoint(option.rect.width() - 17 * g_Widget->widthScalabilityFactor(), option.rect.y() + option.rect.height() - 1));
    painter->restore();
}

QSize GeneralDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //    qDebug() << "GeneralDelegate::sizeHint" << CustomItemDelegate::sizeHint(option, index) << option.rect;
//    return QSize(896 * g_Widget->widthScalabilityFactor(), 92 * g_Widget->heightScalabilityFactor());
    return CustomItemDelegate::sizeHint(option, index);
}
