#ifndef SWITCHITEMWIDGET_H
#define SWITCHITEMWIDGET_H

#include <QPushButton>
#include <QMessageBox>
#include <QTimer>
#include <DGuiApplicationHelper>

class DDESwitchAppletWidget : public QWidget
{
    Q_OBJECT

private:

    QPushButton *IntelCard;
    QPushButton *NvidiaCard;
    
    QTimer *RefreshTimer;
    QString CardName;

private slots:
    void ChangeIntelCard();
    void ChangeNvidiaCard();

public:
    explicit DDESwitchAppletWidget(QWidget *parent = nullptr);

    QString GetCardName();
    void UpdateConfig();
    void UpdateCardName();
    void UpdateCardIcon();
};

#endif