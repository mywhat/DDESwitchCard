#include "DDESwitchAppletWidget.h"
#include "DDEUtil.h"

DGUI_USE_NAMESPACE

DDESwitchAppletWidget::DDESwitchAppletWidget(QWidget *parent) : 
        QWidget(parent),
        RefreshTimer(new QTimer(this))
{
    resize(28, 56);

    IntelCard = new QPushButton(this);
    IntelCard->resize(28, 28);
    IntelCard->move(0, 0);
    NvidiaCard = new QPushButton(this);
    NvidiaCard->resize(28, 28);
    NvidiaCard->move(0, 28);

    //设置10s定时器
    RefreshTimer->start(10000);

    connect(IntelCard, SIGNAL(clicked(bool)), this, SLOT(ChangeIntelCard()));
    connect(NvidiaCard, SIGNAL(clicked(bool)), this, SLOT(ChangeNvidiaCard()));
    connect(RefreshTimer, &QTimer::timeout, this, &DDESwitchAppletWidget::UpdateCardName);
    connect(RefreshTimer, &QTimer::timeout, this, &DDESwitchAppletWidget::UpdateCardIcon);
    UpdateCardName();
    UpdateCardIcon();
}

QString DDESwitchAppletWidget::GetCardName()
{
    return this->CardName;
}

void DDESwitchAppletWidget::ChangeIntelCard()
{
    if(this->CardName == "Intel"){
        qDebug() << "Intel";
        QMessageBox::about(NULL, "Tips", tr("已经是Intel显卡了"));
        return;
    }
    qDebug() << "ChangeIntel";
    
    system("pkexec /opt/switchcard/Intel.sh");
}

void DDESwitchAppletWidget::ChangeNvidiaCard()
{
    if(this->CardName == "Nvidia"){
        qDebug() << "Nvidia";
        QMessageBox::about(NULL, "Tips", tr("已经是Nvidia显卡了"));
        return;
    }
    qDebug() << "ChangeNvidia";

    system("pkexec /opt/switchcard/Nvidia.sh");
}

void DDESwitchAppletWidget::UpdateConfig()
{
    QFile Config(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + ConfigFilePath);
    Config.open(QIODevice::WriteOnly | QIODevice::Truncate);
    Config.write(CardName.toUtf8());
    Config.close();
}

void DDESwitchAppletWidget::UpdateCardName()
{
    QFile Config(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + ConfigFilePath);
    Config.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray TextByte = Config.readAll();
    
    this->CardName = QString(TextByte);
        if(this->CardName.isEmpty()){
            this->CardName.append("Intel");
            this->UpdateConfig();
        }
        Config.close();
}

void DDESwitchAppletWidget::UpdateCardIcon()
{
    QString IntelIconPath(IntelIconDarkPath);
    QString NvidiaIconPath(NvidiaIconDarkPath);
    
    if(DGuiApplicationHelper::instance() -> themeType() == DGuiApplicationHelper::DarkType){
        IntelIconPath = IntelIconLightPath;
        NvidiaIconPath = NvidiaIconLightPath;
    }

    IntelCard->setIcon(QIcon(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+IntelIconPath));
    NvidiaCard->setIcon(QIcon(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+NvidiaIconPath));
}
