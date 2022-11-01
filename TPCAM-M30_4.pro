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
    BaseDialog.cpp

HEADERS  += MainWindow.h \
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
    BaseDialog.h

FORMS    += MainWindow.ui \
    LoginWidget.ui \
    MainMenuWidget.ui \
    DateTimeWidget.ui \
    MainMenuContentWidget.ui \
    IndicatorWidget.ui \
    SettingWidget.ui \
    SelfTestWidget.ui \
    BaseDialog.ui

RESOURCES += \
    style.qrc
