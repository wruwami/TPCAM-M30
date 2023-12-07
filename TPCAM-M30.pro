#-------------------------------------------------
#
# Project created by QtCreator 2022-10-29T10:58:36
#
#-------------------------------------------------

QT       += core gui multimediawidgets multimedia serialport network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TPCAM-M30
TEMPLATE = app

DEFINES+="QT_AVPLAYER_MULTIMEDIA"
INCLUDEPATH += .
include(QtAVPlayer/QtAVPlayer.pri)

SOURCES += main.cpp\
    Application.cpp \
    FileManager.cpp \
    FileTransThread.cpp \
    FtpTransThread.cpp \
    FtpTransThread2.cpp \
    HUDManager.cpp \
    HeadUpDisplay.cpp \
    ImageConverter.cpp \
    IndicatorCameraFocusWidget.cpp \
    IndicatorDialog.cpp \
    LcdBrightManager.cpp \
    LightManager.cpp \
    Logger.cpp \
    MainWindow.cpp \
    LoginWidget.cpp \
    MainMenuWidget.cpp \
    MovieViewerDialog.cpp \
    MovieViewerDialogSub.cpp \
    NetworkAccessManager.cpp \
    NetworkManager.cpp \
    Print.cpp \
    RemoteControlWorker.cpp \
    RemoteController.cpp \
    ScreenSaver.cpp \
    SdCardMemoryLack.cpp \
    SelfTestWidget.cpp \
    SerialGPSManager.cpp \
    SerialLaserManager.cpp \
    SerialPacket.cpp \
    SerialViscaManager.cpp \
    Setting4APWidget.cpp \
    SoundPlayer.cpp \
    SpeedUnitManager.cpp \
    StillImageViewerDialog.cpp \
    StorageManager.cpp \
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
    FileManagerSnapShotDialog.cpp \
    ViscaPacket.cpp \
    camera.cpp \
    capture_thread.cpp \
    filter.cpp \
    keyboard/key.cpp \
    keyboard/keyboard.cpp \
    keyboard/keylayout.cpp \
    LoginExpiredDateWidget.cpp \
    SelfTestWarningMessageWidget.cpp \
    IndicatorGPSWidget.cpp \
    LocationWidget.cpp \
    SystemInfoWidget.cpp \
    FactoryDefaultWidget.cpp \
    AdminPWWidget.cpp \
    PasswordChangingWidget.cpp \
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
    thermal_printer.cpp \
    v4l2_thread.cpp \
    wifi_scan.c \
    GstShmMgr.cpp


HEADERS  += MainWindow.h \
    Application.h \
    FileManager.h \
    FileTransThread.h \
    FontSize.h \
    FtpTransThread.h \
    FtpTransThread2.h \
    HUDManager.h \
    HeadUpDisplay.h \
    ImageConverter.h \
    IndicatorCameraFocusWidget.h \
    IndicatorDialog.h \
    LcdBrightManager.h \
    LightManager.h \
    Logger.h \
    LoginWidget.h \
    MainMenuWidget.h \
    MovieViewerDialog.h \
    MovieViewerDialogSub.h \
    NetworkAccessManager.h \
    NetworkManager.h \
    Print.h \
    RemoteControlWorker.h \
    RemoteController.h \
    ScreenSaver.h \
    SdCardMemoryLack.h \
    SelfTestWidget.h \
    SerialGPSManager.h \
    SerialLaserManager.h \
    SerialPacket.h \
    SerialViscaManager.h \
    Setting4APWidget.h \
    SoundPlayer.h \
    SpeedUnitManager.h \
    StillImageViewerDialog.h \
    StorageManager.h \
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
    FileManagerSnapShotDialog.h \
    ViscaPacket.h \
    base.h \
    camera.h \
    capture_thread.h \
    filter.h \
    keyboard/key.h \
    keyboard/keyboard.h \
    keyboard/keylayout.h \
    LoginExpiredDateWidget.h \
    SelfTestWarningMessageWidget.h \
    IndicatorGPSWidget.h \
    LocationWidget.h \
    SystemInfoWidget.h \
    FactoryDefaultWidget.h \
    AdminPWWidget.h \
    PasswordChangingWidget.h \
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
    thermal_printer.h \
    v4l2_thread.h \
    wifi_scan.h \
    version.h \
    QtAVPlayer/qavandroidsurfacetexture_p.h \
    QtAVPlayerHelper/videorenderer.h \
    QtAVPlayerHelper/mediaservice.h \
    QtAVPlayerHelper/mediaobject.h \
    QtAVPlayerHelper/videowidget.h \
    GstShmMgr.h

FORMS    += MainWindow.ui \
    IndicatorCameraFocusWidget.ui \
    IndicatorDialog.ui \
    LoginWidget.ui \
    MainMenuWidget.ui \
    DateTimeWidget.ui \
    MainMenuContentWidget.ui \
    MovieViewerDialog.ui \
    MovieViewerDialogSub.ui \
    SdCardMemoryLack.ui \
    SelfTestWidget.ui \
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
    SelfTestWarningMessageWidget.ui \
    IndicatorGPSWidget.ui \
    LocationWidget.ui \
    StillImageViewerDialog.ui \
    SystemInfoWidget.ui \
    FactoryDefaultWidget.ui \
    AdminPWWidget.ui \
    PasswordChangingWidget.ui \
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

OTHER_FILES += start.sh \
               command_change.sh \
               command_origin.sh

RESOURCES += \
    style.qrc

DISTFILES +=

unix:!macx: LIBS += -L/usr/local/lib/ \
        -lhangul \
        -lavformat\
        -lswscale\
        -lavcodec\
        -lavutil\
        -lopencv_core \
        -lopencv_imgcodecs \
        -lopencv_imgproc \
        -lopencv_objdetect \
        -lopencv_video \
        -lopencv_videoio \
        -lmnl \
        -lftp++ \
        -lpthread

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

top_builddir=$$shadowed($$PWD)
QMAKE_POST_LINK += "rm -rf $$top_builddir/settings/build_date.txt" $$escape_expand(\n\t)
QMAKE_POST_LINK += "date +"%Y%m%d" >> $$top_builddir/settings/build_date.txt" $$escape_expand(\n\t)

# copies the given files to the destination directory
defineTest(copyToDestDir) {
    files = $$1
    dir = $$2

    for(file, files) {
        QMAKE_POST_LINK += $$QMAKE_COPY_DIR $$shell_quote($$file) $$shell_quote($$dir) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}

CONFIG += force_debug_info

#copyToDestDir(srcPath, destPath)
copyToDestDir($$PWD/start.sh, $$OUT_PWD)
copyToDestDir($$PWD/command_origin.sh, $$OUT_PWD)
copyToDestDir($$PWD/command_change.sh, $$OUT_PWD)
