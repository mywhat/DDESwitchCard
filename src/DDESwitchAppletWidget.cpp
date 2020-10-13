#include "DDESwitchAppletWidget.h"
#include "DDEUtil.h"

DGUI_USE_NAMESPACE

DDESwitchAppletWidget::DDESwitchAppletWidget(QWidget *parent) : 
        QWidget(parent),
        RefreshTimer(new QTimer(this))
{
    resize(32, 96);

    Intel = new QPushButton(this);
    Intel->resize(32, 32);
    Intel->move(0, 0);
    Nvidia = new QPushButton(this);
    Nvidia->resize(32, 32);
    Nvidia->move(0, 32);
    Hybrid = new QPushButton(this);
    Hybrid->resize(32, 32);
    Hybrid->move(0, 64);

    //设置10s定时器
    RefreshTimer->start(10000);

    connect(Intel, SIGNAL(clicked(bool)), this, SLOT(SwitchIntel()));
    connect(Nvidia, SIGNAL(clicked(bool)), this, SLOT(SwitchNvidia()));
    connect(Hybrid, SIGNAL(clicked(bool)), this, SLOT(SwitchHybrid()));
    connect(RefreshTimer, &QTimer::timeout, this, &DDESwitchAppletWidget::UpdateCardName);
    connect(RefreshTimer, &QTimer::timeout, this, &DDESwitchAppletWidget::UpdateCardIcon);
    UpdateCardName();
    UpdateCardIcon();
}

QString DDESwitchAppletWidget::GetCardName()
{
    return this->CardName;
}

void DDESwitchAppletWidget::SwitchIntel()
{
    if(this->CardName == "Intel"){
        qDebug() << "Intel";
        QMessageBox(QMessageBox::NoIcon, "Tips", tr("当前已是Intel显卡"), \
                                 QMessageBox::Ok, NULL, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint).exec();
        return;
    }
    qDebug() << "ChangeIntel";
        
    if(!this->SwitchAction("Intel")){
        QMessageBox(QMessageBox::NoIcon, "Tips", tr("切换Intel显卡失败"), \
                                 QMessageBox::Ok, NULL, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint).exec();
        return;
    }

    this->CardName = "Intel";

}

void DDESwitchAppletWidget::SwitchNvidia()
{
    if(this->CardName == "Nvidia"){
        qDebug() << "Nvidia";
        QMessageBox(QMessageBox::NoIcon, "Tips", tr("当前已是Nvidia显卡"), \
                                 QMessageBox::Ok, NULL, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint).exec();    }
    qDebug() << "ChangeNvidia";

    if(!this->SwitchAction("Nvidia")){
        QMessageBox(QMessageBox::NoIcon, "Tips", tr("切换Nvidia显卡失败"), \
                                 QMessageBox::Ok, NULL, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint).exec();
        return;
    }

    this->CardName = "Nvidia";

}

void DDESwitchAppletWidget::SwitchHybrid()
{
    if(this->CardName == "Hybrid"){
        qDebug() << "Hybrid";
        QMessageBox(QMessageBox::NoIcon, "Tips", tr("当前已是Intel和Nvidia混合输出"), \
                                 QMessageBox::Ok, NULL, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint).exec();
    }

    if(!this->SwitchAction(QString("Hybrid"))){
        QMessageBox(QMessageBox::NoIcon, "Tips", tr("切换Prime方案失败"), \
                                 QMessageBox::Ok, NULL, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint).exec();
        return;
    }

    this->CardName = "Hybrid";

}

bool DDESwitchAppletWidget::SwitchAction(QString name)
{
    FILE *file = NULL;
    char temp[256] = {0};
    bool isOK = false;

    if(name == "Intel"){
        file = popen("pkexec /opt/apps/switchcard/switchCard.sh -s Intel", "r");
    }
    else if (name == "Nvidia") {
        file = popen("pkexec /opt/apps/switchcard/switchCard.sh -s Nvidia", "r");
    }
    else {
        file = popen("pkexec /opt/apps/switchcard/switchCard.sh -s Hybrid", "r");
    }

    if(!file){
        QMessageBox(QMessageBox::NoIcon, "Tips", tr("popen打开管道出错!!\n无法切换显卡！！"), \
                                 QMessageBox::Ok, NULL, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint).exec();
        return isOK;
    }

    while(memset(temp, 0, sizeof(temp)) && fgets(temp, sizeof(temp), file)){
        if(!strncmp(temp, "Success", sizeof("Success") - 1)){
            isOK = true;
            break;
        }
    }

    pclose(file);
    return isOK;
}

void DDESwitchAppletWidget::UpdateCardName()
{
    FILE *file = NULL;
    char temp[64] = {0};

    if(!(file = popen("/opt/apps/switchcard/switchCard.sh -c", "r"))){
        QMessageBox(QMessageBox::NoIcon, "Tips", tr("popen打开管道出错!!\n无法获取显卡名字！！"), \
                                 QMessageBox::Ok, NULL, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint).exec();
        return;
    }

    if(!fgets(temp, sizeof(temp), file)){
        QMessageBox(QMessageBox::NoIcon, "Tips", tr("无法获取脚本输出!!"), \
                                 QMessageBox::Ok, NULL, Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint).exec();
        pclose(file);
        return;
    }
    pclose(file);
    this->CardName = QString(temp).replace("\n", "");
}

void DDESwitchAppletWidget::UpdateCardIcon()
{
/*    QString IntelIconPath(IntelIconDarkPath);
    QString NvidiaIconPath(NvidiaIconDarkPath);
    QString HybridIconPath(HybridIconDarkPath);
    
    if(DGuiApplicationHelper::instance() -> themeType() == DGuiApplicationHelper::DarkType){
        IntelIconPath = IntelIconLightPath;
        NvidiaIconPath = NvidiaIconLightPath;
        HybridIconPath = HybridIconLightPath;
    }
*/
    Intel->setIcon(QIcon(IntelIconPath));
    Nvidia->setIcon(QIcon(NvidiaIconPath));
    Hybrid->setIcon(QIcon(HybridIconPath));
    Intel->setIconSize(QSize(32, 32));
    Nvidia->setIconSize(QSize(32, 32));
    Hybrid->setIconSize(QSize(32, 32));
}
