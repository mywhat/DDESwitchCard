#include "DDESwitchWidget.h"
#include "DDEUtil.h"

DDESwitchWidget::DDESwitchWidget(QWidget *parent)
    : QWidget(parent)
    , m_infoLabel(new QLabel)
    , m_refreshTimer(new QTimer(this))
    , m_appletWidget(new DDESwitchAppletWidget)
{
    m_infoLabel->setStyleSheet("QLabel {"
                               "color: white;"
                               "}");
    m_infoLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(m_infoLabel);
    centralLayout->setSpacing(0);
    centralLayout->setMargin(0);

    setLayout(centralLayout);

    // 连接 Timer 超时的信号到更新数据的槽上
    connect(m_refreshTimer, &QTimer::timeout, this, &DDESwitchWidget::RefreshInfo);

    // 设置 Timer 超时为 10s，即每 10s 更新一次控件上的数据，并启动这个定时器
    m_refreshTimer->start(10000);

    RefreshInfo();
}

void DDESwitchWidget::RefreshInfo()
{
    // 更新内容
    m_infoLabel->setText(QString("%1").arg(QString(m_appletWidget->GetCardName())));
}
