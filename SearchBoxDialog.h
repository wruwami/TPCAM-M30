/**
 * @file SearchBoxDialog.h
 * @author wruwami (wruwami@naver.com)
 * @brief 파일매니저 검색 다이얼로그
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SEARCHBOXDIALOG_H
#define SEARCHBOXDIALOG_H

#include <QDialog>

namespace Ui {
class SearchBoxDialog;
}

class SearchBoxDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchBoxDialog(QString, QWidget *parent = 0);
    ~SearchBoxDialog();
    int getFirstValue() const;
    void setFirstValue(int value);

    int getSecondValue() const;
    void setSecondValue(int value);

private slots:
    void on_firstPlusButton_clicked();

    void on_firstMinusButton_clicked();

    void on_secondPlusButton_clicked();

    void on_secondMinusButton_clicked();

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();
    void on_searchButton_clicked();

private:
    Ui::SearchBoxDialog *ui;
    int firstValue = 0;
    int secondValue = 60;
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // SEARCHBOXDIALOG_H
