#ifndef SDCARDMEMORYLACK_H
#define SDCARDMEMORYLACK_H

#include <QWidget>

namespace Ui {
class SdCardMemoryLack;
}

class SdCardMemoryLack : public QWidget
{
    Q_OBJECT

public:
    explicit SdCardMemoryLack(QWidget *parent = nullptr);
    ~SdCardMemoryLack();

private:
    Ui::SdCardMemoryLack *ui;
};

#endif // SDCARDMEMORYLACK_H
