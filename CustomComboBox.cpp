#include "CustomComboBox.h"

#include <QStyledItemDelegate>
#include <QProxyStyle>

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

        QProxyStyle::drawItemText(painter, rect, Qt::AlignCenter, pal, enabled, text, textRole);
    }
};

CustomComboBox::CustomComboBox(QWidget *parent) : QComboBox(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    setStyle(new AlignComboBoxProxy);
//    setItemDelegate(new AlignDelegate(Qt::AlignCenter, this));
}

void CustomComboBox::resizeEvent(QResizeEvent *event)
{
    QFont font;
    font.setPointSizeF(this->width()/FontSize::Maximum); // /40은 창크기에 따른 비례 값으로 디버깅하면서 변경해야한다.
    if(font.pointSizeF()<=FontSize::Minimum) //최소폰트 설정
        font.setPointSizeF(FontSize::Minimum);
    this->setFont(font); //설정된 폰트를 위젯에 적용
}
