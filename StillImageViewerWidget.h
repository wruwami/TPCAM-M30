#ifndef STILLIMAGEVIEWERWIDGET_H
#define STILLIMAGEVIEWERWIDGET_H

#include <QWidget>

namespace Ui {
class StillImageViewerWidget;
}

class StillImageViewerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StillImageViewerWidget(QWidget *parent = 0);
    ~StillImageViewerWidget();

private:
    Ui::StillImageViewerWidget *ui;
};

#endif // STILLIMAGEVIEWERWIDGET_H
