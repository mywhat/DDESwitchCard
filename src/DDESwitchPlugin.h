#ifndef SWITCHCARD_H
#define SWITCHCARD_H

#include <dde-dock/pluginsiteminterface.h>
#include <QObject>
#include <QLabel>

#include "DDESwitchWidget.h"
#include "DDESwitchAppletWidget.h"

class DDESwitchPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    // 声明实现了的接口
    Q_INTERFACES(PluginsItemInterface)
    // 插件元数据
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "DDESwitchPlugin.json")

public:
    explicit DDESwitchPlugin(QObject *parent = nullptr);

    // 返回插件的名称，必须是唯一值，不可以和其它插件冲突
    const QString pluginName() const override;

    // 插件初始化函数
    void init(PluginProxyInterface *proxyInter) override;

    // 返回插件的 widget
    QWidget *itemWidget(const QString &itemKey) override;
    QWidget *itemTipsWidget(const QString &itemKey) override;
    QWidget *itemPopupApplet(const QString &itemKey) override;
private:
    DDESwitchWidget *m_pluginWidget;
    QLabel *m_tipsWidget;
    DDESwitchAppletWidget *m_appletWidget;
};

#endif // HOMEMONITORPLUGIN_H