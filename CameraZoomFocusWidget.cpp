#include "CameraZoomFocusWidget.h"
#include "ui_CameraZoomFocusWidget.h"

#include <QHeaderView>

#include "StringLoader.h"

CameraZoomFocusWidget::CameraZoomFocusWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraZoomFocusWidget)
{
    ui->setupUi(this);

    ui->zoomLabel->setText("Z: 2FCE");
    ui->focusLabel->setText("F: 1585");

    ui->optPushButton->setText(LoadString("IDS_OPT"));
    ui->focusPlusPushButton->setText(LoadString("IDS_FOCUS_PLIS"));
    ui->FocusMinusPushButton->setText(LoadString("IDS_FOCUS_MINUS"));

    ui->dayComboBox->addItem(LoadString("IDS_DAY"));
    ui->dayComboBox->addItem(LoadString("IDS_NIGHT"));

    ui->autoTriggerPushButton->setText(LoadString("IDS_AT"));
    ui->initPushButton->setText(LoadString("IDS_INIT"));

    ui->zoomRangeLabel->setText(LoadString("IDS_ZOOM_60_100"));
    ui->dzPlusPushButton->setText(LoadString("IDS_DZ_PLUS"));
    ui->dzMinusPushButton->setText(LoadString("IDS_DZ_MINUS"));

    ui->pgrsSavePushButton->setText(LoadString("IDS_PQRS_SAVE"));
    ui->jpgSavePushButton->setText(LoadString("IDS_JPG_SAVE"));

//    ui->tableWidget->setColumnWidth(0, ui->pgrsSavePushButton->width() / 2);
//    ui->tableWidget->setColumnWidth(1, ui->pgrsSavePushButton->width() * 1.5);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList rowHeaders;
    rowHeaders.append(LoadString("IDS_DAY"));
    rowHeaders.append(LoadString("IDS_NIGHT"));
    ui->tableWidget->setHorizontalHeaderLabels(rowHeaders);

    QStringList columnHeaders;
    columnHeaders.append(LoadString("IDS_Z10"));
    columnHeaders.append(LoadString("IDS_Z30"));
    columnHeaders.append(LoadString("IDS_Z60"));
    columnHeaders.append(LoadString("IDS_Z100"));
    columnHeaders.append(LoadString("IDS_Z160"));
    columnHeaders.append(LoadString("IDS_Z260"));
    ui->tableWidget->setVerticalHeaderLabels(columnHeaders);

    m_serialViscaManager.connectVisca();
}

CameraZoomFocusWidget::~CameraZoomFocusWidget()
{
    m_serialViscaManager.close();
    delete ui;
}

void CameraZoomFocusWidget::on_optPushButton_clicked()
{
    m_serialViscaManager.set_AF_one_push_trigger();
}


void CameraZoomFocusWidget::on_focusPlusPushButton_clicked()
{
    m_serialViscaManager.plus_focus();
}


void CameraZoomFocusWidget::on_FocusMinusPushButton_clicked()
{
    m_serialViscaManager.minus_focus();
}

