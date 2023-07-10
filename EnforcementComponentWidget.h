#ifndef ENFORCEMENTCOMPONENTWIDGET_H
#define ENFORCEMENTCOMPONENTWIDGET_H

#include <QWidget>
#include <QJsonObject>
#include <QQueue>
#include <list>
#include <vector>
#include "ConfigManager.h"

enum Mode{
    Ready,
    AT,
    Manual,
};

class Camera;
class CustomPushButton;
namespace Ui {
class EnforcementComponentWidget;
}

class EnforcementComponentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EnforcementComponentWidget(QWidget *parent = 0);
    virtual ~EnforcementComponentWidget();
    friend class RemoteController;
    void dzPlus();
    void dzMinus();
    void SaveImage();

private:
    void hide();
    void show();
    void setOutFrame(bool isSet);
    void SetCamera();
    void camInit();
    void hudInit();
    void laserInit();
private:
    bool m_bHide = false;
    bool m_isSetOutLine = false;
    ConfigManager m_config = ConfigManager("parameter_setting1.json");
    ConfigManager m_config2 = ConfigManager("parameter_setting2.json");
    QJsonObject m_object;
    QJsonObject m_object2;
    QJsonObject m_object3;
    bool m_UserModeOn;
    std::vector<QString> m_stvector = {"60", "80", "100", "120", "140", "160", "180", "200", "220", "240", "260"};
    std::vector<QString> m_ltvector = {"10~36", "30~60", "60~100", "100~160", "160~260", "260+"};
    int m_nStIndex = 2;
    int m_nLtIndex = 3;
    Camera* m_pCamera = nullptr;
    Mode m_nMode = Ready;
private slots:
    void on_hidePushButton_clicked();
    void doShartAction();
    void on_zoomRangePushButton_clicked();

    void on_readyPushButton_clicked();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::EnforcementComponentWidget *ui;
};

#endif // ENFORCEMENTCOMPONENTWIDGET_H
