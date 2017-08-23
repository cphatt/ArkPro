#ifndef MESSAGEBOXWIDGET
#define MESSAGEBOXWIDGET

#include <QWidget>
#include <QScopedPointer>

class MessageBoxWidgetPrivate;
class MessageBoxWidget : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MessageBoxWidget)
public:
    explicit MessageBoxWidget(QWidget *parent = NULL);
    ~MessageBoxWidget();
protected:
    void customEvent(QEvent* event);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    friend class MessageBoxWidgetPrivate;
    QScopedPointer<MessageBoxWidgetPrivate> m_Private;
};

#endif // MESSAGEBOXWIDGET
