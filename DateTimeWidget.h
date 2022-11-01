#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include <QWidget>

namespace Ui {
class DateTimeWidget;
}

class DateTimeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DateTimeWidget(QWidget *parent = 0);
    ~DateTimeWidget();

private:
    Ui::DateTimeWidget *ui;
};

#endif // DATETIMEWIDGET_H
