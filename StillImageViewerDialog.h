#ifndef STILLIMAGEVIEWERDIALOG_H
#define STILLIMAGEVIEWERDIALOG_H

#include <QDialog>

namespace Ui {
class StillImageViewerDialog;
}

class StillImageViewerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StillImageViewerDialog(QWidget *parent = 0);
    ~StillImageViewerDialog();

private slots:
    void on_quitPushButton_clicked();

private:
    Ui::StillImageViewerDialog*ui;
};

#endif // STILLIMAGEVIEWERDIALOG_H
