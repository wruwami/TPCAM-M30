/**
 * @file SdCardMemoryLack.h
 * @author wruwami (wruwami@naver.com)
 * @brief sdcard 용량 부족 표시 위젯 baseDialog에 삽입된다.
 * @version 0.1
 * @date 2023-12-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef SDCARDMEMORYLACK_H
#define SDCARDMEMORYLACK_H

#include <QWidget>

namespace Ui {
class SdCardMemoryLack;
}

/**
 * @brief sdcard 용량 부족 표시 위젯 클래스
 * 
 */
class SdCardMemoryLack : public QWidget
{
    Q_OBJECT

public:
    explicit SdCardMemoryLack(QString msg, QWidget *parent = nullptr);
    ~SdCardMemoryLack();
private:
    QDialog* m_pParent;
private slots:
    void on_pushButton_clicked();

private:
    Ui::SdCardMemoryLack *ui;
};

#endif // SDCARDMEMORYLACK_H
