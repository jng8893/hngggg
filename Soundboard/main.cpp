#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // sets up audioManager and adds sounds
    AudioManager *audioManager = new AudioManager();
    audioManager->addSound(new QFile(":/sounds/hat.wav"));
    audioManager->addSound(new QFile(":/sounds/kick.wav"));
    audioManager->addSound(new QFile(":/sounds/perc_1.wav"));
    audioManager->addSound(new QFile(":/sounds/perc_2.wav"));
    audioManager->addSound(new QFile(":/sounds/perc_3.wav"));
    audioManager->addSound(new QFile(":/sounds/snare_1.wav"));
    audioManager->addSound(new QFile(":/sounds/snare_2.wav"));

    // sets up Main Window
    MainWindow w;
    w.setAudioManager(audioManager);
    w.show();

    return a.exec();
}
