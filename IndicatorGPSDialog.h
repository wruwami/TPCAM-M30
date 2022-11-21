#ifndef INDICATORGPSDIALOG_H
#define INDICATORGPSDIALOG_H

#include <QDialog>

namespace Ui {
class IndicatorGpsDialog;
}

class IndicatorGpsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IndicatorGpsDialog(QWidget *parent = 0);
    ~IndicatorGpsDialog();

private:
    Ui::IndicatorGpsDialog *ui;
};

#endif // INDICATORGPSDIALOG_H
