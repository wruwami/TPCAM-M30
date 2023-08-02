#include "CustomComboBox.h"

#include <QStyledItemDelegate>
#include <QProxyStyle>
#include <QResizeEvent>
#include <QLineEdit>

#include "FontSize.h"

class AlignDelegate: public QStyledItemDelegate{
public:
    AlignDelegate(Qt::Alignment alignment, QObject *parent = nullptr):
        QStyledItemDelegate(parent), m_alignment(alignment)
    {

    }
protected:
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const
    {
        QStyledItemDelegate::initStyleOption(option, index);
        option->displayAlignment = m_alignment;
    }
    Qt::Alignment m_alignment;
};

class AlignComboBoxProxy: public QProxyStyle{
public:
    using QProxyStyle::QProxyStyle;
    void drawItemText(QPainter *painter,
                      const QRect &rect,
                      int /*flags*/,
                      const QPalette &pal,
                      bool enabled,
                      const QString &text,
                      QPalette::ColorRole textRole) const
    {

        QProxyStyle::drawItemText(painter, rect, Qt::AlignLeft | Qt::AlignVCenter, pal, enabled, text, textRole);
    }
};

CustomComboBox::CustomComboBox(QWidget *parent) : QComboBox(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    setEditable(true);
//    lineEdit()->setDisabled(true);
//    lineEdit()->setAlignment(Qt::AlignVCenter);
//    lineEdit()->setReadOnly(true);
    setStyle(new AlignComboBoxProxy);
    setItemDelegate(new AlignDelegate(Qt::AlignLeft | Qt::AlignVCenter, this));
//    setStyleSheet(QString("QComboBox::down-arrow { image: url(images/Main_menu/combobox_drop_down_arrow.jpg);}"));
    QFile file(":/style/customComboBox.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());

    setStyleSheet(styleSheet);
//    this->setEditable(true);
}

//void CustomComboBox::setText(QString text)
//{
//   QLineEdit *displayedText = this->lineEdit();
//   displayedText->setText(text);
//   displayedText->setReadOnly(true);
//}

void CustomComboBox::resizeEvent(QResizeEvent *event)
{
    QFont font;
    font.setPointSizeF(this->width()/FontSize::Maximum); // /40은 창크기에 따른 비례 값으로 디버깅하면서 변경해야한다.
    if(font.pointSizeF()<=FontSize::Minimum) //최소폰트 설정
        font.setPointSizeF(FontSize::Minimum);
    this->setFont(font); //설정된 폰트를 위젯에 적용

    QFile file(":/style/customComboBox.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());

    setStyleSheet(QString(styleSheet + "QComboBox QListView {text-align:center;}\
QListView::item {height: %0px;}").arg(event->size().height()));
}
