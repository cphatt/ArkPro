#ifndef TABBAR_H
#define TABBAR_H

#include "BusinessLogic/Widget/Widget.h"
#include <QWidget>
#include <QScopedPointer>

class TabBarWidgetPrivate;
class TabBarWidget
        : protected QWidget
        , protected Widget::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(TabBarWidget)
public:
    explicit TabBarWidget(QWidget *parent = NULL);
    ~TabBarWidget();
protected:
    void showEvent(QShowEvent* event);
    void customEvent(QEvent* event);
    void resizeEvent(QResizeEvent *event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private slots:
    void onTabBarButtonRelease();
private:
    friend class TabBarWidgetPrivate;
    friend class BmpButton;
    QScopedPointer<TabBarWidgetPrivate> m_Private;
};

#endif // TABBAR_H
