#ifndef INFORMATIONWIDGET_H
#define INFORMATIONWIDGET_H

#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>

#include "DDESwitchAppletWidget.h"

class DDESwitchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DDESwitchWidget(QWidget *parent = nullptr);

private slots:
    // 用于更新数据的槽函数
    void RefreshInfo();

private:
    // 真正的数据显示在这个 Label 上
    QLabel *m_infoLabel;
    // 处理时间间隔的计时器
    QTimer *m_refreshTimer;

    DDESwitchAppletWidget *m_appletWidget;

};

#endif // INFORMATIONWIDGET_H
