/**
 * @file FileManagerErrorMessageWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 열전사 프린터 연결 실패 시 메시지 보여주는 위젯 BaseDialog에 삽입된다.
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef FILEMANAGERERRORMESSAGEWIDGET_H
#define FILEMANAGERERRORMESSAGEWIDGET_H

#include <QWidget>

namespace Ui {
class FileManagerErrorMessageWidget;
}

class FileManagerErrorMessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileManagerErrorMessageWidget(QWidget *parent = 0);
    ~FileManagerErrorMessageWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FileManagerErrorMessageWidget *ui;
    QDialog* m_pParent;
};

#endif // FILEMANAGERERRORMESSAGEWIDGET_H
