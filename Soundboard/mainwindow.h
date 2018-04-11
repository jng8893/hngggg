#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "audiomanager.h"
#include <QMainWindow>
#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setAudioManager(AudioManager *audioManager);

private:
    Ui::MainWindow *ui;
    AudioManager *audioManager;

    QFrame *topFrame;
    QVBoxLayout *vBox;
    std::vector<QHBoxLayout*> hBoxes;
    QPushButton *newSoundButton;

    QFrame *bottomFrame;
    QHBoxLayout *hBox;
    QPushButton *playButton;
    QPushButton *loopButton;
    QPushButton *recordButton;
    QPushButton *saveButton;

private slots:
    void newSoundClicked();
    void playClicked();
    void loopClicked();
    void recordClicked();
    void saveClicked();
};

#endif // MAINWINDOW_H
