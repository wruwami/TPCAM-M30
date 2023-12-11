#include "Application.h"
#include "ScreenSaver.h"

#include "FileManager.h"

Application::Application(int &argc, char **argv):
    QApplication(argc,argv)
{
   _screensaver=new screensaver;
   soundPlayer = new SoundPlayer("button.mp3");
}

Application::~Application()
{
    delete _screensaver;
    delete soundPlayer;
}
bool Application::notify(QObject *obj, QEvent *e)
{
    if(e->type() ==QEvent::MouseButtonPress )
    {
        soundPlayer->play();

        if (_screensaver->Getstart())
        {
            if(_screensaver->timeisactive())
            {
                _screensaver->timestart();
            }
            else
            {
                _screensaver->screensaverstop();
            }
        }

    }
    return QApplication::notify(obj,e);
}
screensaver* Application::send()
{
    return _screensaver;
}



