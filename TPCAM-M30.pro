#-------------------------------------------------
#
# Project created by QtCreator 2022-10-29T10:58:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TPCAM-M30_4
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    LoginWidget.cpp \
    MainMenuWidget.cpp \
    StringLoader.cpp \
    DateTimeWidget.cpp \
    MainMenuContentWidget.cpp \
    IndicatorWidget.cpp \
    SettingWidget.cpp \
    SelfTestWidget.cpp \
    CustomCheckBox.cpp \
    CustomComboBox.cpp \
    CustomLabel.cpp \
    CustomLineEdit.cpp \
    CustomPushButton.cpp \
    BaseDialog.cpp \
    Setting1Widget.cpp \
    Setting2Widget.cpp \
    Setting3Widget.cpp \
    Setting4Widget.cpp \
    Setting5Widget.cpp \
    Setting6Widget.cpp \
    Setting7Widget.cpp \
    EnforcementWidget.cpp \
    FileManagementWidget.cpp \
    EnforcementSpeedReady.cpp \
    EnforcementCamera.cpp

HEADERS  += MainWindow.h \
    FontSize.h \
    LoginWidget.h \
    MainMenuWidget.h \
    StringLoader.h \
    Color.h \
    DateTimeWidget.h \
    MainMenuContentWidget.h \
    IndicatorWidget.h \
    SettingWidget.h \
    SelfTestWidget.h \
    CustomCheckBox.h \
    CustomComboBox.h \
    CustomLabel.h \
    CustomLineEdit.h \
    CustomPushButton.h \
    BaseDialog.h \
    Setting1Widget.h \
    Setting2Widget.h \
    Setting3Widget.h \
    Setting4Widget.h \
    Setting5Widget.h \
    Setting6Widget.h \
    Setting7Widget.h \
    EnforcementWidget.h \
    FileManagementWidget.h \
    EnforcementSpeedReady.h \
    EnforcementCamera.h

FORMS    += MainWindow.ui \
    LoginWidget.ui \
    MainMenuWidget.ui \
    DateTimeWidget.ui \
    MainMenuContentWidget.ui \
    IndicatorWidget.ui \
    SettingWidget.ui \
    SelfTestWidget.ui \
    BaseDialog.ui \
    Setting1Widget.ui \
    Setting2Widget.ui \
    Setting3Widget.ui \
    Setting4Widget.ui \
    Setting5Widget.ui \
    Setting6Widget.ui \
    Setting7Widget.ui \
    EnforcementWidget.ui \
    FileManagementWidget.ui \
    EnforcementSpeedReady.ui \
    EnforcementCamera.ui

RESOURCES += \
    style.qrc
