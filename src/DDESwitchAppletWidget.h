#ifndef SWITCHITEMWIDGET_H
#define SWITCHITEMWIDGET_H

#include <QPushButton>
#include <QTimer>
#include <DGuiApplicationHelper>
#include <DMessageBox>

class DDESwitchAppletWidget : public QWidget
{
    Q_OBJECT

private:

    QPushButton *Intel;
    QPushButton *Nvidia;
    QPushButton *Hybrid;

    QTimer *RefreshTimer;
    QString CardName;

    bool SwitchAction(QString name);

private slots:
    void SwitchIntel();
    void SwitchNvidia();
    void SwitchHybrid();

public:
    explicit DDESwitchAppletWidget(QWidget *parent = nullptr);

    QString GetCardName();
    void UpdateCardName();
    void UpdateCardIcon();
};

#endif
