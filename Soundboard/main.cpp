#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // sets up audioManager and adds sounds
    AudioManager *audioManager = new AudioManager();
    for (int i = 0; i < 7; i++) {
        audioManager->addSound(new QFile("sound_" + QString::number(i) + ".wav"));
    }

    // sets up Main Window
    MainWindow w;
    w.setAudioManager(audioManager);
    w.show();

    return a.exec();
}
