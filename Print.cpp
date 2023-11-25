#include "Print.h"

#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include <QTextCursor>
#include <QDate>

#include "StringLoader.h"
#include "FileManager.h"
#include "DateFormatManager.h"

Print::Print(AVFileFormat avFileFormat, QImage image)
{
    QTextDocument doc;
//    doc.setTextWidth()
    QTextCursor cursor(&doc);

    QPixmap pixmap;
    pixmap.load(GeteMMCPath() + "/" + "images" + "/" + "booting" + "/" + "comlaser_logo.bmp");
    QImage logoImage = pixmap.toImage();

    cursor.insertImage(logoImage);
    QTextCharFormat textFormat;
    textFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
    QFont font = textFormat.font();
    font.setPixelSize(15);
    textFormat.setFont(font);


    cursor.insertText(LoadString("IDS_POLICE_OVER_SPEEDING_TICKET"), textFormat);

//    QTextFrameFormat frameFormat;
//    frameFormat.setHeight(10);
//    frameFormat.setWidth(612);
//    QColor line = QColor(47, 104, 172);
//    frameFormat.setBackground(line);
//    cursor.insertFrame(frameFormat);
//    cursor.insert
    pixmap.load(GeteMMCPath() + "/" + "images" + "/" + "booting" + "/" + "blueLine.png");
    pixmap = pixmap.scaledToWidth(612, Qt::SmoothTransformation);
    logoImage = pixmap.toImage();
    cursor.insertImage(logoImage);

    font.setPixelSize(15);
    textFormat.setFont(font);

    cursor.insertBlock();
    cursor.insertBlock();
    cursor.insertText(LoadString("IDS_DEVICE_ID") + " : " + avFileFormat.deviceId, textFormat);
    cursor.insertBlock();
    cursor.insertBlock();
    cursor.insertText(LoadString("IDS_UN") + " : " + avFileFormat.userId, textFormat);
    cursor.insertBlock();
    cursor.insertBlock();
    cursor.insertText(LoadString("IDS_DATE") + " : " + GetDate(QString(avFileFormat.date).mid(0, 8)), textFormat);
    cursor.insertBlock();
    cursor.insertBlock();
    QString time = QString(avFileFormat.time).mid(0, 2) + ":" + QString(avFileFormat.time).mid(2, 2) + ":" + QString(avFileFormat.time).mid(4, 2);
    cursor.insertText(LoadString("IDS_TIME") + " : " + time, textFormat);
    cursor.insertBlock();
    cursor.insertBlock();
    QString speedUnit;
    QString distanceUnit;
    if (QString(avFileFormat.unit) == "S")
    {
        speedUnit = "Km/h";
        distanceUnit = "meter";
    }
    else
    {
        speedUnit = "mph";
        distanceUnit = "feet";
    }

    cursor.insertText(LoadString("IDS_SPEED_LIMIT") + " : " + QString::number(avFileFormat.speedLimit.toInt()) + " " + speedUnit, textFormat);
    cursor.insertBlock();
    cursor.insertBlock();
    int captureSpeed;
    if (avFileFormat.captureSpeed.mid(0,1) == "M")
    {
        captureSpeed = -(avFileFormat.captureSpeed.mid(1,4).toInt());
    }
    else
    {
        captureSpeed = (avFileFormat.captureSpeed.mid(1,4).toInt());
    }
    cursor.insertText(LoadString("IDS_VIOLATION_SPEED") + " : "+ QString::number(captureSpeed) + " " + speedUnit, textFormat);
    cursor.insertBlock();
    cursor.insertBlock();
    cursor.insertText(LoadString("IDS_RANGE") + " : " + QString::number(avFileFormat.distance.toInt()) + " " + distanceUnit, textFormat);
    cursor.insertBlock();
    cursor.insertBlock();
    cursor.insertText(LoadString("IDS_LOCATION") + " : " + avFileFormat.location + "(" + avFileFormat.latitude + "," + avFileFormat.longitude + ")", textFormat);
    cursor.insertBlock();
    cursor.insertBlock();


//    QPixmap pixmap2;
//    pixmap2.fromImage();
//    pixmap2 = pixmap2.scaled(612,344, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    image = image.scaled(612,344, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

//    QImage logoImage2 = pixmap2.toImage();
    cursor.insertImage(image);
    cursor.insertBlock();
    cursor.insertBlock();

    pixmap.load(GeteMMCPath() + "/" + "images" + "/" + "booting" + "/" + "blueLine.png");
    pixmap = pixmap.scaledToWidth(612, Qt::SmoothTransformation);
    logoImage = pixmap.toImage();
    cursor.insertImage(logoImage);

//    cursor.insertFrame(frameFormat);

    cursor.insertBlock();
    cursor.insertText(LoadString("IDS_PRINT_DATE") + " : " + GetDate(QDate::currentDate().toString("yyyyMMdd")), textFormat);
    cursor.insertBlock();
    cursor.insertBlock();
    cursor.insertText(LoadString("IDS_OFFIEC_ID") + " : ", textFormat);
    textFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
    cursor.insertText("                  ", textFormat);

    textFormat.setUnderlineStyle(QTextCharFormat::NoUnderline);

    cursor.insertText("                  " + LoadString("IDS_SIGNATURE") + " : ", textFormat);
    textFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
    cursor.insertText("                  ", textFormat);


//    doc.setHtml();

    QPrinter printer;
    QPrintDialog dialog(&printer);
    if (dialog.exec() == QDialog::Accepted)
    {
        doc.print(&printer);
    }
}
