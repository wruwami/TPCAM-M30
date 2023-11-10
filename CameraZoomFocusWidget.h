#ifndef CAMERAZOOMFOCUSWIDGET_H
#define CAMERAZOOMFOCUSWIDGET_H

#include <QWidget>
#include <QMap>

#include "SerialViscaManager.h"
#include "ConfigManager.h"
#include "HUDManager.h"
#include "base.h"

class Camera;
class CustomLabel;
class SerialLaserManager;
namespace Ui {
class CameraZoomFocusWidget;
}

class CameraZoomFocusWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraZoomFocusWidget(QWidget *parent = 0);
    virtual ~CameraZoomFocusWidget();
    void SetCamera(Camera* camera);
    void setPSerialLaserManager(SerialLaserManager *newPSerialLaserManager);

    void setPSerialViscaManager(SerialViscaManager *newPSerialViscaManager);
    void setMainMenuSize(QSize);
private:
    void ZoomRange();
    void SetLaserDetectionAreaDistance(int zoom_index);
    void setTableInit();
    void setTableDefualtInit();
    void checkButtonEnable();
    void setFocusEditJsonInit();
    void SaveJpg();
    void ModifyFocusEditJson(int, int, int = 1);
    void SaveFocusJson();
    void SaveFocusEditJson();
    void SaveDZoomJson();
    void SetStValue(int index, QJsonArray& ar, QJsonArray& ar2);
    void SendViscaValue();
    void EditTableValue();
    void EditTableValue2();
    void SetTableVerticalHeader();
    void camInit();
    void laserInit();
    void setZoomGoal(int zoom_index);
    void setFocusGoal(int zoom_index, int ndaynight);

private:
    ConfigManager m_configManager = ConfigManager("exposure.json");
    ConfigManager m_coofigManager2 = ConfigManager("focus_edit.json");
    ConfigManager m_coofigManager3 = ConfigManager("focus.json");
    QJsonObject m_object;
    QJsonObject m_object2;
    QJsonObject m_object3;
    QString m_strDZoom;
    std::map<std::pair<int,int>, QString> m_MapFocus;
    QTimer m_ClearTimer;
    QString m_currentFocus;

    QString m_zoomGoal, m_focusGoal, m_dzoomGoal;
    QPoint m_LaserPoint;
    CustomLabel* m_pSpeedSensitivitylabel;
private slots:
    void on_optPushButton_clicked();

    void on_focusPlusPushButton_clicked();

    void on_FocusMinusPushButton_clicked();

    void on_dayComboBox_currentIndexChanged(int index);

    void on_initPushButton_clicked();

    void on_zoomRangePushButton_clicked();

    void on_dzPlusPushButton_clicked();

    void on_dzMinusPushButton_clicked();

    void on_showDistance(float,int);
    void on_jpgSavePushButton_clicked();

    void on_pgrsSavePushButton_clicked();

//    void on_autoTriggerPushButton_toggled(bool checked);
    void on_show_dzoom(QString);
    void on_show_zoom(QString);
    void on_show_focus(QString);

    void ClearDisplay();

    void on_autoTriggerPushButton_clicked(bool checked);

    void on_tableWidget_cellClicked(int row, int column);

private:
    QSize m_pMainMenuWidgetSize;
    Ui::CameraZoomFocusWidget *ui;
    SerialViscaManager* m_pSerialViscaManager;
    Camera* m_pCamera;
    size_t m_nLtIndex = 2;
    size_t m_nDNIndex = 0;
    SerialLaserManager* m_pSerialLaserManager = nullptr;
    bool m_UserModeOn;
    std::vector<QString> m_ltmetervector;// = {"10~36", "30~60", "60~100", "100~160", "160~260", "260+"};
    bool m_bATChecked;
    QPoint m_nTableIndex;
//    QMap<QPoint, int> m_mTableStatus;   // int 0 not jpg,pqrs, 1 not pqrs, 2 all complete
    std::map<std::pair<int,int>, int> m_mTableStatus;   // int 0 not jpg,pqrs, 1 not pqrs, 2 all complete
    HUDManager m_hud;
//    QPoint m_nTableStatus;

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // CAMERAZOOMFOCUSWIDGET_H
