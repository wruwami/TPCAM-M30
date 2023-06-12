#-------------------------------------------------
#
# Project created by QtCreator 2022-10-29T10:58:36
#
#-------------------------------------------------

QT       += core gui multimediawidgets serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TPCAM-M30_4
TEMPLATE = app


SOURCES += main.cpp\
    CustomTogglePushButton.cpp \
    FileManager.cpp \
    HUDManager.cpp \
    HeadUpDisplay.cpp \
    ImageConverter.cpp \
    IndicatorCameraFocusWidget.cpp \
    IndicatorDialog.cpp \
    LcdBrightManager.cpp \
    LightManager.cpp \
    MainWindow.cpp \
    LoginWidget.cpp \
    MainMenuWidget.cpp \
    MovieViewerDialog.cpp \
    NetworkAccessManager.cpp \
    NetworkManager.cpp \
    RemoteControlWorker.cpp \
    RemoteController.cpp \
    SdcardManager.cpp \
    SelfTestDialog.cpp \
    SerialGPSManager.cpp \
    SerialLaserManager.cpp \
    SerialPacket.cpp \
    SerialViscaManager.cpp \
    Setting4APWidget.cpp \
    StillImageViewerDialog.cpp \
    StringLoader.cpp \
    DateTimeWidget.cpp \
    MainMenuContentWidget.cpp \
    SettingWidget.cpp \
    CustomComboBox.cpp \
    CustomCheckBox.cpp \
    CustomLabel.cpp \
    CustomLineEdit.cpp \
    CustomPushButton.cpp \
    BaseDialog.cpp \
    Setting1Widget.cpp \
    Setting2Widget.cpp \
    Setting3Widget.cpp \
    Setting5Widget.cpp \
    Setting6Widget.cpp \
    Setting7Widget.cpp \
    EnforcementWidget.cpp \
    EnforcementComponentWidget.cpp \
    FileManagerWidget.cpp \
    MainMenuAdminAlignWidget.cpp \
    DeviceIDWidget.cpp \
    CameraAlignWidget.cpp \
    CameraZoomFocusWidget.cpp \
    CustomImageWidget.cpp \
    FileManagerSnapShotDialog.cpp \
    ViscaPacket.cpp \
    filter.cpp \
    keyboard/key.cpp \
    keyboard/keyboard.cpp \
    keyboard/keylayout.cpp \
    LoginExpiredDateWidget.cpp \
    FileManagerFileTransferWidget.cpp \
    SelfTestWarningMessageWidget.cpp \
    IndicatorGPSWidget.cpp \
    LocationWidget.cpp \
    SystemInfoWidget.cpp \
    FactoryDefaultWidget.cpp \
    AdminPWWidget.cpp \
    PasswordChangingWidget.cpp \
    NetworkPWWidget.cpp \
    WifiSearchWidget.cpp \
    BluetoothSearchFilterWidget.cpp \
    EnforcementWarningMessageWidget.cpp \
    FileManagerErrorMessageWidget.cpp \
    FileManagerQuestionMessageWidget.cpp \
    WidgetSize.cpp \
    Setting4STAWidget.cpp \
    HomeTitleWidget.cpp \
    HomeButtonWidget.cpp \
    KeyboardDialog.cpp \
    KeypadDialog.cpp \
    IndicatorCameraExposeWidget.cpp \
    CustomList.cpp \
    CustomScrollbar.cpp \
    ConfigManager.cpp \
    DateFormatManager.cpp \
    SearchBoxWidget.cpp \
    CustomZoomLabel.cpp \
    FileManagerFileTransferDialog.cpp \
    SearchBoxDialog.cpp \
    ltc2943.cpp \
    thermal_printer.cpp


HEADERS  += MainWindow.h \
    CustomTogglePushButton.h \
    FileManager.h \
    FontSize.h \
    HUDManager.h \
    HeadUpDisplay.h \
    ImageConverter.h \
    IndicatorCameraFocusWidget.h \
    IndicatorDialog.h \
    LcdBrightManager.h \
    LightManager.h \
    LoginWidget.h \
    MainMenuWidget.h \
    MovieViewerDialog.h \
    NetworkAccessManager.h \
    NetworkManager.h \
    RemoteControlWorker.h \
    RemoteController.h \
    SdcardManager.h \
    SelfTestDialog.h \
    SerialGPSManager.h \
    SerialLaserManager.h \
    SerialPacket.h \
    SerialViscaManager.h \
    Setting4APWidget.h \
    StillImageViewerDialog.h \
    StringLoader.h \
    Color.h \
    DateTimeWidget.h \
    MainMenuContentWidget.h \
    SettingWidget.h \
    CustomCheckBox.h \
    CustomComboBox.h \
    CustomLabel.h \
    CustomLineEdit.h \
    CustomPushButton.h \
    BaseDialog.h \
    Setting1Widget.h \
    Setting2Widget.h \
    Setting3Widget.h \
    Setting5Widget.h \
    Setting6Widget.h \
    Setting7Widget.h \
    EnforcementWidget.h \
    EnforcementComponentWidget.h \
    FileManagerWidget.h \
    MainMenuAdminAlignWidget.h \
    DeviceIDWidget.h \
    CameraAlignWidget.h \
    CameraZoomFocusWidget.h \
    CustomImageWidget.h \
    ImageSize.h \
    FileManagerSnapShotDialog.h \
    ViscaPacket.h \
    filter.h \
    keyboard/key.h \
    keyboard/keyboard.h \
    keyboard/keylayout.h \
    LoginExpiredDateWidget.h \
    FileManagerFileTransferWidget.h \
    SelfTestWarningMessageWidget.h \
    IndicatorGPSWidget.h \
    LocationWidget.h \
    SystemInfoWidget.h \
    FactoryDefaultWidget.h \
    AdminPWWidget.h \
    PasswordChangingWidget.h \
    NetworkPWWidget.h \
    WifiSearchWidget.h \
    BluetoothSearchFilterWidget.h \
    EnforcementWarningMessageWidget.h \
    FileManagerErrorMessageWidget.h \
    FileManagerQuestionMessageWidget.h \
    WidgetSize.h \
    Setting4STAWidget.h \
    HomeTitleWidget.h \
    HomeButtonWidget.h \
    KeyboardDialog.h \
    KeypadDialog.h \
    IndicatorCameraExposeWidget.h \
    CustomList.h \
    CustomScrollbar.h \
    ltc2943.h \
    rapidcsv.h \
    ConfigManager.h \
    DateFormatManager.h \
    FileFormat.h \
    SearchBoxWidget.h \
    CustomZoomLabel.h \
    FileManagerFileTransferDialog.h \
    SearchBoxDialog.h \
    thermal_printer.h

FORMS    += MainWindow.ui \
    IndicatorCameraFocusWidget.ui \
    IndicatorDialog.ui \
    LoginWidget.ui \
    MainMenuWidget.ui \
    DateTimeWidget.ui \
    MainMenuContentWidget.ui \
    MovieViewerDialog.ui \
    SelfTestDialog.ui \
    Setting4APWidget.ui \
    SettingWidget.ui \
    BaseDialog.ui \
    Setting1Widget.ui \
    Setting2Widget.ui \
    Setting3Widget.ui \
    Setting5Widget.ui \
    Setting6Widget.ui \
    Setting7Widget.ui \
    EnforcementWidget.ui \
    EnforcementComponentWidget.ui \
    FileManagerWidget.ui \
    MainMenuAdminAlignWidget.ui \
    DeviceIDWidget.ui \
    CameraAlignWidget.ui \
    CameraZoomFocusWidget.ui \
    FileManagerSnapShotDialog.ui \
    LoginExpiredDateWidget.ui \
    FileManagerFileTransferWidget.ui \
    SelfTestWarningMessageWidget.ui \
    IndicatorGPSWidget.ui \
    LocationWidget.ui \
    StillImageViewerDialog.ui \
    SystemInfoWidget.ui \
    FactoryDefaultWidget.ui \
    AdminPWWidget.ui \
    PasswordChangingWidget.ui \
    NetworkPWWidget.ui \
    WifiSearchWidget.ui \
    BluetoothSearchFilterWidget.ui \
    EnforcementWarningMessageWidget.ui \
    FileManagerErrorMessageWidget.ui \
    FileManagerQuestionMessageWidget.ui \
    Setting4STAWidget.ui \
    HomeTitleWidget.ui \
    HomeButtonWidget.ui \
    KeyboardDialog.ui \
    KeypadDialog.ui \
    IndicatorCameraExposeWidget.ui \
    SearchBoxWidget.ui \
    FileManagerFileTransferDialog.ui \
    SearchBoxDialog.ui

RESOURCES += \
    style.qrc

DISTFILES +=

unix:!macx: LIBS += -L/usr/local/lib/ -lhangul -lavformat -lswscale -lavformat -lavcodec -lavutil

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include
