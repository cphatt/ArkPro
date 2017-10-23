#ifndef TIMESELECT_H
#define TIMESELECT_H

#include <QWidget>
#include <QScopedPointer>

class TimeSelectPrivate;
class TimeSelect : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(TimeSelect)
public:
    explicit TimeSelect(QWidget* parent = NULL);
    ~TimeSelect();
    void setNum(const int data);
    int getNum();
    void setText(const QString text);
protected:
    void resizeEvent(QResizeEvent* event);

protected slots:
    void minusBtnRelease();
    void plusBtnRelease();

private:
    friend class TimeSelectPrivate;
    QScopedPointer<TimeSelectPrivate> m_Private;
};


#endif // TIMESELECT_H
