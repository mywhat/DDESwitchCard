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

const QString DDESwitchPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    QList<QVariant> items;
    items.reserve(2);

    QMap<QString, QVariant> refresh;
    refresh["itemId"] = "refresh";
    refresh["itemText"] = "Refresh";
    refresh["isActive"] = true;
    items.push_back(refresh);

    QMap<QString, QVariant> reload;
    reload["itemId"] = "reload lightdm";
    reload["itemText"] = "Reload Lightdm";
    reload["isActive"] = true;
    items.push_back(reload);

    QMap<QString, QVariant> menu;
    menu["items"] = items;
    menu["checkableMenu"] = false;
    menu["singleCheck"] = false;

    // 返回 JSON 格式的菜单数据
    return QJsonDocument::fromVariant(menu).toJson();
}

void DDESwitchPlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(itemKey);

    // 根据上面接口设置的 id 执行不同的操作
    if (menuId == "refresh") {
        m_appletWidget->GetCardName();
    } else if (menuId == "reload lightdm") {
        system("pkexec /opt/apps/switchcard/reloadLightdm.sh");
    }
}
