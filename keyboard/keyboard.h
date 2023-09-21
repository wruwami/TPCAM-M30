#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QStackedWidget>
#include <QString>
#include <QFile>
enum InputMode { Undefined, Mouse, keyboard, Keypad, Keypad2, Mixed, DatePicker };
enum Langauge { English, Arabic, Spanish, French, Korean, Portuguese};
class KeyLayout;
class Key;
class Keyboard : public QStackedWidget {
    Q_OBJECT

public:
    explicit Keyboard(QFile &iJsonFile, InputMode iInputMode = InputMode::Undefined, QWidget *iParent = nullptr);
    ~Keyboard();
    // Key *findKeyFromString(const QString &name, const int &layout);
    KeyLayout *GetKeyLayout();
    Langauge nLangauge() const;

    void setNLangauge(Langauge newNLangauge);
private:
    QString LanguagePrefix();
    Langauge LanguageCode();
private:
    QWidget* m_parent;
    /*protected:
        void mouseMoveEvent(QMouseEvent *e) override;*/
signals:

    void keyPressed(QString t);
    void backspacePressed();
    void returnPressed();

private slots:
    void onKeyPressed(const QString &iKey, Key* mKey);

private:
    // Key *currentKey;
    // char currentindexkeyboard;
    Langauge m_nLangauge;
    KeyLayout *_keylayout;
    InputMode _inputMode = Undefined;
};

#endif    // KEYBOARD_H
