#include "DDESwitchPlugin.h"
#include "DDEUtil.h"

DDESwitchPlugin::DDESwitchPlugin(QObject *parent)
    : QObject(parent)
{

}

const QString DDESwitchPlugin::pluginName() const
{
    return QStringLiteral("Switch Video Card");
}

void DDESwitchPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;
    
    m_pluginWidget = new DDESwitchWidget;
    m_tipsWidget = new QLabel;
    m_appletWidget = new DDESwitchAppletWidget;

    m_proxyInter->itemAdded(this, pluginName());
}

//dock栏插件显示
QWidget *DDESwitchPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    // 这里暂时返回空指针，这意味着插件会被 dde-dock 加载
    // 但是不会有任何东西被添加到 dde-dock 上
    return this->m_pluginWidget;
}

//鼠标悬停时显示信息
QWidget *DDESwitchPlugin::itemTipsWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    // 设置/刷新 tips 中的信息
    m_tipsWidget->setText(QString("%1").arg(m_appletWidget->GetCardName()));

    return this->m_tipsWidget;
}

QWidget *DDESwitchPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return this->m_appletWidget;
}