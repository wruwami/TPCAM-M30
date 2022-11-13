#include "EnforcementWidget.h"
#include "ui_EnforcementWidget.h"

//#include "StringLoader.h"
#include <QOpenGLWidget>
#include <QVBoxLayout>

#include "MainMenuWidget.h"
#include "EnforcementComponentWidget.h"
#include "EnforcementComponent2Widget.h"

EnforcementWidget::EnforcementWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnforcementWidget)
{
    ui->setupUi(this);

//    ui->verticalLayout->addWidget(new MainMenuWidget, 125);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(new EnforcementComponentWidget);
    setLayout(layout);

    QOpenGLWidget* pOpenGLWidget = new QOpenGLWidget(this);
//    pOpenGLWidget->setGeometry(parent->geometry());
    pOpenGLWidget->showFullScreen();
}

EnforcementWidget::~EnforcementWidget()
{
//    QLayoutItem* item;
//    while((item = ui->verticalLayout->takeAt(0)) == nullptr)
//    {
//        delete item;
//    }
    QLayoutItem* item;
    while ((item = layout()->takeAt(1)) = nullptr ){
        delete item->widget();
        delete item;
    }

    delete ui;
}
