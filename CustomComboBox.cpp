#include "CustomComboBox.h"

#include <QStyledItemDelegate>
#include <QProxyStyle>
#include <QResizeEvent>
#include <QLineEdit>
#include <QFont>
#include <QAbstractItemView>
#include <QAbstractScrollArea>
#include <QScrollBar>
#include <QApplication>
#include <QDesktopWidget>
#include <QCompleter>
#include <QDebug>
#include "FileManager.h"

#include "FontSize.h"
#include "WidgetSize.h"

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
    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
    this->view()->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
    this->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
//    this->view()->setMaximumWidth()
    this->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    this->view()->verticalScrollBar()->setStyleSheet("width: 15px;");
    view()->installEventFilter(this);

//    this->view()->verticalScrollBar().resize();
//    this->setEnabled(true);
//    completer()->setCompletionMode(QCompleter::PopupCompletion);

    setStyle(new AlignComboBoxProxy);
    setItemDelegate(new AlignDelegate(Qt::AlignLeft | Qt::AlignVCenter, this));
//    setStyleSheet(QString("QComboBox::down-arrow { image: url(images/Main_menu/combobox_drop_down_arrow.jpg);}"));
//    QFile file(":/style/customComboBox.qss");
//    file.open(QFile::ReadOnly);
    QString styleSheet = QString("QComboBox \
    { \
        combobox-popup: 0;\
        border-width: 2px;\
        border-style: solid;\
    }\
    \
    QComboBox::drop-down\
    {\
        width : 35px;\
        border: none;\
    }\
    QComboBox::down-arrow {\
        image: url(%0images/Main_menu/combobox_drop_down_arrow.bmp);\
        width: 30px;\
        height: 30px;\
    }\
    \
    QScrollBar:vertical {\
     border: 2px solid black;\
     width: 50px;\
     margin : 52px 0 52px 0;\
     background : white;\
    }\
    QScrollBar::handle:vertical{\
     min-height: 20px;\
    }\
    QScrollBar::add-line:vertical {\
     border: 2px solid black;\
     height: 50px;\
     subcontrol-position: bottom;\
     subcontrol-origin: margin;\
     image: url(%0images/Main_menu/combobox_drop_down_arrow.bmp);\
    }\
    QScrollBar::sub-line:vertical {\
     border: 2px solid black;\
     height: 50px;\
     subcontrol-position: top;\
     subcontrol-origin: margin;\
     image: url(%0images/Main_menu/combobox_drop_up_arrow.jpg);\
    } \
").arg(GeteMMCPath() + "/");

    setStyleSheet(styleSheet);
    this->setMaxVisibleItems(6);

//    QAbstractItemView *qv = this->view();
//    QScrollBar *scrollbar = qv->verticalScrollBar();
//    m_size = scrollbar->size();
//    m_size.setWidth(m_size.width() * 3);
//    scrollbar->resize(m_size);
//    this->view()->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 100px; }");
//    qv->setVerticalScrollBar(
//    this->setView(qv);
//    this->view()->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 30px; }\
//                                           QScrollBar::handle:vertical{\
//                                               min-height: 50px;\
//                                           }\
//                                           QScrollBar::add-line:vertical {\
//                                               border: solid 1px black;\
//                                               height: 30px;\
//                                               subcontrol-position: bottom;\
//                                               subcontrol-origin: margin;\
//                                           }\
//                                           QScrollBar::sub-line:vertical {\
//                                               border: solid 1px black;\
//                                               height: 30px;\
//                                             subcontrol-position: top;\
//                                             subcontrol-origin: margin;\
//                                           }");
                                                     qDebug() << this->view()->verticalScrollBar()->styleSheet();
}

void CustomComboBox::setFontSize(int font_size)
{
    int calc_font_size = GetFontSize(font_size);
    QFont font = this->font();
    font.setPixelSize(calc_font_size);
    this->setFont(font);
}

void CustomComboBox::showPopup()
{

//    QComboBox::showPopup();
    bool oldAnimationEffects = qApp->isEffectEnabled(Qt::UI_AnimateCombo);
    qApp->setEffectEnabled(Qt::UI_AnimateCombo, false);

    QComboBox::showPopup();
    qApp->setEffectEnabled(Qt::UI_AnimateCombo, oldAnimationEffects);



//    QWidget *popup = this->findChild<QFrame*>(); //    if (popup->rect().y() > 130)
//    qDebug() << popup->geometry();
//    popup->move(popup->x(), popup->y()+popup->height());
//    popup->move(popup->x(),popup->y()-this->height()-popup->height());
//    popup->move(QApplication::desktop()->screen()->rect().center() - popup->rect().center());

//    QSizePolicy sp = view()->sizePolicy();
//    sp.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
//    view()->move(QApplication::desktop()->screen()->rect().center() - view()->rect().center());
//    view()->    view()->setSizePolicy(sp);
}

//void CustomComboBox::setText(QString text)
//{
//   QLineEdit *displayedText = this->lineEdit();
//   displayedText->setText(text);
//   displayedText->setReadOnly(true);
//}

bool CustomComboBox::eventFilter(QObject *o, QEvent *e)
{
  bool handled = false;
  if (e->type() == QEvent::Show)
  {
    if (o == view())
    {
      QWidget *popup = findChild<QFrame*>();

      QString qstrObjName = o->parent()->parent()->objectName();

      if(qstrObjName == "timeZoneComboBox")
        popup->resize(int(popup->width()*2.2f), popup->height());
      else if(qstrObjName == "gainComboBox"
        || qstrObjName == "irisComboBox"
        || qstrObjName == "shutterSpeedComboBox"
        || qstrObjName == "dnrComboBox")
        popup->resize(int(popup->width()*1.4f), popup->height());

      popup->move(QApplication::desktop()->screen()->rect().center() - popup->rect().center());


      //For some reason, the frame's geometry is GLOBAL, not relative to the QComboBox!
//      frame->move(frame->x(),
//                  mapToGlobal(lineEdit()->geometry().topLeft()).y() - frame->height());
    }
  }
  /*else if other filters here*/

  if (!handled)
    handled = QComboBox::eventFilter(o, e);

  return handled;
}

void CustomComboBox::resizeEvent(QResizeEvent *event)
{
     QComboBox::resizeEvent(event);
//    QFont font;
//    font.setPointSizeF(this->width()/FontSize::Maximum); // /40은 창크기에 따른 비례 값으로 디버깅하면서 변경해야한다.
//    if(font.pointSizeF()<=FontSize::Minimum) //최소폰트 설정
//        font.setPointSizeF(FontSize::Minimum);
//    this->setFont(font); //설정된 폰트를 위젯에 적용

    QFile file(":/style/customComboBox.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());

    setStyleSheet(QString("QComboBox \
                                                   { \
                                                       combobox-popup: 0;\
                                                       border-width: 2px;\
                                                       border-style: solid;\
                                                   }\
                                                   \
                                                   QComboBox::drop-down\
                                                   {\
                                                       width : 35px;\
                                                       border: none;\
                                                   }\
                                                   QComboBox::down-arrow {\
                                                       image: url(%0images/Main_menu/combobox_drop_down_arrow.bmp);\
                                                       width: 30px;\
                                                       height: 30px;\
                                                   }\
                                                   \
                                                   QScrollBar:vertical {\
                                                    border: 2px solid black;\
                                                    width: 50px;\
                                                    margin : 52px 0 52px 0;\
                                                    background : white;\
                                                   }\
                                                   QScrollBar::handle:vertical{\
                                                    min-height: 20px;\
                                                   }\
                                                   QScrollBar::add-line:vertical {\
                                                    border: 2px solid black;\
                                                    height: 50px;\
                                                    subcontrol-position: bottom;\
                                                    subcontrol-origin: margin;\
                                                    image: url(%0images/Main_menu/combobox_drop_down_arrow.bmp);\
                                                   }\
                                                   QScrollBar::sub-line:vertical {\
                                                    border: 2px solid black;\
                                                    height: 50px;\
                                                    subcontrol-position: top;\
                                                    subcontrol-origin: margin;\
                                                    image: url(%0images/Main_menu/combobox_drop_up_arrow.jpg);\
                                                   } \
                                               ").arg(GeteMMCPath() + "/").arg(event->size().height() * 3 / 4));
//    this->view()->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { width: 30px; }\
//                                           QScrollBar::handle:vertical{\
//                                               min-height: 30px;\
//                                           }\
//                                           QScrollBar::add-line:vertical {\
//                                               height: 30px;\
//                                               subcontrol-position: bottom;\
//                                               subcontrol-origin: margin;\
//                                           }\
//                                           QScrollBar::sub-line:vertical {\
//                                               height: 30px;\
//                                             subcontrol-position: up;\
//                                             subcontrol-origin: margin;\
//                                           }");

//    QWidget *popup = findChild<QFrame*>();\
//            popup->resize(event->size().width() ,event->size().height()  * 6);

//    QWidget *popup = this->findChild<QFrame*>(); //    if (popup->rect().y() > 130)
//    popup->move(QApplication::desktop()->screen()->rect().center() - popup->rect().center());
//    this->view()->setStyleSheet()
}
