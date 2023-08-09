#include "EnforcementWidget.h"
#include "ui_EnforcementWidget.h"

//#include "StringLoader.h"
//#include <QOpenGLWidget>
#include <QOpenGLWidget>
#include <QVBoxLayout>

#include "MainMenuWidget.h"
#include "EnforcementComponentWidget.h"

EnforcementWidget::EnforcementWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnforcementWidget)
{
    ui->setupUi(this);

//    ui->verticalLayout->addWidget(new MainMenuWidget, 125);
    QVBoxLayout* layout = new QVBoxLayout;
    m_pEnforcementComponentWidget = new EnforcementComponentWidget;
    layout->addWidget(m_pEnforcementComponentWidget);
    layout->setMargin(0);
    setLayout(layout);


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

    if (m_pEnforcementComponentWidget != nullptr)
    {
        delete m_pEnforcementComponentWidget;
        m_pEnforcementComponentWidget = nullptr;
    }

    delete ui;
}
