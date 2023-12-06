/**
 * @file FileManagerQuestionMessageWidget.h
 * @author wruwami (wruwami@naver.com)
 * @brief 파일매니저에서 SDCard 삭제 시 표시되는 위젯 BaseDialog에 삽입된다.
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef FILEMANAGERQUESTIONMESSAGEWIDGET_H
#define FILEMANAGERQUESTIONMESSAGEWIDGET_H

#include <QWidget>

class QDialog;
namespace Ui {
class FileManagerQuestionMessageWidget;
}

class FileManagerQuestionMessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileManagerQuestionMessageWidget(QWidget *parent = 0);
    ~FileManagerQuestionMessageWidget();

private slots:
    void on_okPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::FileManagerQuestionMessageWidget *ui;
    QDialog* m_pParent;
};

#endif // FILEMANAGERQUESTIONMESSAGEWIDGET_H
