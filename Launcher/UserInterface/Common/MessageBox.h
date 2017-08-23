#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QWidget>
#include <QScopedPointer>

class MessageBoxPrivate;
class MessageBox : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MessageBox)
public:
    enum Type {
        T_Show = 0,
        T_Hide = 1,
    };
    explicit MessageBox(QWidget *parent = NULL);
    ~MessageBox();
    void setText(const QString &text);
    void setAutoHide(const bool flag);
    void setFontPointSize(const int pointSize);
protected:
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent* event);
    void hideEvent(QHideEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void messageWidgetChange(const MessageBox::Type type);
    void messageShowTimeout();
private slots:
    void onTimeOut();
private:
    friend class MessageBoxPrivate;
    QScopedPointer<MessageBoxPrivate> m_Private;
};

#endif // MESSAGEBOX_H
