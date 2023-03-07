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
    explicit StillImageViewerDialog(QString file_path, QWidget *parent = 0);
    ~StillImageViewerDialog();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_quitPushButton_clicked();

    void on_plusPushButton_clicked();

    void on_minusPushButton_clicked();

    void on_originPushButton_clicked();
    
private:
    Ui::StillImageViewerDialog*ui;
    QString m_file_path;
    double m_factor = 1;
};

#endif // STILLIMAGEVIEWERDIALOG_H
