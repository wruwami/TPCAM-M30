#ifndef MOVIEVIEWERWIDGET_H
#define MOVIEVIEWERWIDGET_H

#include <QWidget>

namespace Ui {
class MovieViewerWidget;
}

class MovieViewerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MovieViewerWidget(QWidget *parent = 0);
    ~MovieViewerWidget();

private:
    Ui::MovieViewerWidget *ui;
};

#endif // MOVIEVIEWERWIDGET_H
