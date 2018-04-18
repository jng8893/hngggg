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
    QVBoxLayout *vBox2;
    QHBoxLayout *hBox;
    QHBoxLayout *hBox2;
    QPushButton *playButton;
    QPushButton *loopButton;
    QPushButton *recordButton;
    QPushButton *micButton;
    QPushButton *undoButton;
    QPushButton *saveButton;

    void closeEvent(QCloseEvent *event);

private slots:
    void newSoundClicked();
    void playClicked();
    void loopClicked();
    void recordClicked();
    void micClicked();
    void undoClicked();
    void saveClicked();
    void soundButtonClicked();
};

#endif // MAINWINDOW_H
