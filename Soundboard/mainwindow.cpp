#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
    ui->centralWidget->setGeometry(0, 0, 800, 600);
    ui->centralWidget->setFixedSize(800, 600);

    // adds Frame and VBox for buttons
    topFrame = new QFrame(ui->centralWidget);
    topFrame->setGeometry(0, 0, 800, 400);
    topFrame->setFixedSize(800, 400);
    topFrame->setFrameShadow(QFrame::Sunken);
    topFrame->setFrameStyle(1);
    vBox = new QVBoxLayout(topFrame);

    // adds HBoxes to VBox
    for (int i = 0; i < 2; i++) {
        hBoxes.push_back(new QHBoxLayout());
        hBoxes.back()->setContentsMargins(4, 4, 4, 4);
        hBoxes.back()->setSpacing(4);
        vBox->addLayout(hBoxes.back());
    }

    // adds Sound Buttons to HBoxes
    for (int i = 0; i < 7; i++) {
        QPushButton *newButton = new QPushButton();
        newButton->setFixedSize(150, 75);
        newButton->setText("Sound " + QString::number(i+1));
        newButton->setShortcut(QKeySequence(QString::number(i + 1)));
        hBoxes[i/4]->addWidget(newButton);
    }

    // adds New Sound Button to HBoxes
    newSoundButton = new QPushButton();
    newSoundButton->setFixedSize(150, 75);
    newSoundButton->setText("New Sound");
    newSoundButton->setShortcut(QKeySequence("N"));
    hBoxes.back()->addWidget(newSoundButton);
    connect(newSoundButton, SIGNAL(clicked()), this, SLOT(newSoundClicked()));

    // adds Frame and HBox for control buttons
    bottomFrame = new QFrame(ui->centralWidget);
    bottomFrame->setGeometry(0, 400, 800, 400);
    bottomFrame->setFixedSize(800, 200);
    hBox = new QHBoxLayout(bottomFrame);
    hBox->setContentsMargins(4, 4, 4, 4);
    hBox->setSpacing(4);

    // adds play button to HBox
    playButton = new QPushButton();
    playButton->setFixedSize(150, 75);
    playButton->setText("Play");
    playButton->setCheckable(true);
    hBox->addWidget(playButton);
    connect(playButton, SIGNAL(clicked()), this, SLOT(playClicked()));

    // sets shortcuts
    QShortcut *shortcut_p = new QShortcut(playButton);
    shortcut_p->setKey(QKeySequence("p"));
    connect(shortcut_p, SIGNAL(activated()), playButton, SLOT(click()));
    QShortcut *shortcut_space = new QShortcut(playButton);
    shortcut_space->setKey(QKeySequence(" "));
    connect(shortcut_space, SIGNAL(activated()), playButton, SLOT(click()));

    // adds loop button to HBox
    loopButton = new QPushButton();
    loopButton->setFixedSize(150, 75);
    loopButton->setText("Loop");
    loopButton->setShortcut(QKeySequence("L"));
    hBox->addWidget(loopButton);
    connect(loopButton, SIGNAL(clicked()), this, SLOT(loopClicked()));

    // adds record button to HBox
    recordButton = new QPushButton();
    recordButton->setFixedSize(150, 75);
    recordButton->setText("Record");
    recordButton->setCheckable(true);
    hBox->addWidget(recordButton);
    connect(recordButton, SIGNAL(clicked()), this, SLOT(recordClicked()));

    // sets shortcut
    QShortcut *shortcut_r = new QShortcut(recordButton);
    shortcut_r->setKey(QKeySequence("r"));
    connect(shortcut_r, SIGNAL(activated()), recordButton, SLOT(click()));

    // adds save button to HBox
    saveButton = new QPushButton();
    saveButton->setFixedSize(150, 75);
    saveButton->setText("Save");
    saveButton->setShortcut(QKeySequence("S"));
    hBox->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAudioManager(AudioManager *audioManager) {
    this->audioManager = audioManager;
}

// New Sound Button functionality - opens dialog, adds sound button and adjusts
void MainWindow::newSoundClicked() {
    hBoxes.back()->removeWidget(newSoundButton);

    // adds newButton
    int index = (hBoxes.size() - 2) * 4 + hBoxes.back()->count() - 2;
    QPushButton *newButton = new QPushButton();
    newButton->setFixedSize(150, 75);
    newButton->setText("Custom Sound " + QString::number(index));
    newButton->setShortcut(QKeySequence("F" + QString::number(index)));
    hBoxes.back()->addWidget(newButton);

    // creates new HBox if necessary and possible
    if (hBoxes.size() < 4 && hBoxes.back()->count() == 4) {
        hBoxes.push_back(new QHBoxLayout());
        hBoxes.back()->setContentsMargins(4, 4, 4, 4);
        hBoxes.back()->setSpacing(4);
        vBox->addLayout(hBoxes.back());
    }

    // adds newSoundButton back if possible, disables it otherwise
    if (hBoxes.size() <= 4 && hBoxes.back()->count() < 4)
        hBoxes.back()->addWidget(newSoundButton);
    else
        newSoundButton->setEnabled(false);
}

// Play Button functionality - play or pause track
void MainWindow::playClicked() {
    if (playButton->text().compare(QString("Play")) == 0) {
        playButton->setText("Pause");

        audioManager->play();
    } else {
        playButton->setText("Play");

        audioManager->pause();
    }
}

void MainWindow::loopClicked() {
    audioManager->loop();
}

void MainWindow::recordClicked() {
    if (recordButton->text().compare(QString("Record")) == 0) {
        recordButton->setText("Stop Recording");
    } else {
        recordButton->setText("Record");
    }
}

void MainWindow::saveClicked() {

}

// void MainWindow::soundButtonClicked() {}
