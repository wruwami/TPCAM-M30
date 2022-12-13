#ifndef MOVIEVIEWERDIALOG_H
#define MOVIEVIEWERDIALOG_H

#include <QDialog>

namespace Ui {
class MovieViewerDialog;
}

class MovieViewerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MovieViewerDialog(QWidget *parent = 0);
    ~MovieViewerDialog();

private slots:
    void on_quitPushButton_clicked();

private:
    Ui::MovieViewerDialog*ui;
};

#endif // MOVIEVIEWERDIALOG_H
