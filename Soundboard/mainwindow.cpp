#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // sets up window
    QWidget *window = new QWidget;
    window->setFixedSize(800, 600);

    // adds Frame and VBox for buttons
    topFrame = new QFrame(window);
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

        if (i == 0) {
            newButton->setText("(" + QString::number(i + 1) + ") Hat");
        } else if (i == 1) {
            newButton->setText("(" + QString::number(i + 1) + ") Kick");
        } else if (i == 2) {
            newButton->setText("(" + QString::number(i + 1) + ") Perc 1");
        } else if (i == 3) {
            newButton->setText("(" + QString::number(i + 1) + ") Perc 2");
        } else if (i == 4) {
            newButton->setText("(" + QString::number(i + 1) + ") Perc 3");
        } else if (i == 5) {
            newButton->setText("(" + QString::number(i + 1) + ") Snare 1");
        } else if (i == 6) {
            newButton->setText("(" + QString::number(i + 1) + ") Snare 2");
        }

        newButton->setShortcut(QKeySequence(QString::number(i + 1)));
        hBoxes[i/4]->addWidget(newButton);
        connect(newButton, SIGNAL(clicked()), this, SLOT(soundButtonClicked()));
    }

    // adds New Sound Button to HBoxes
    newSoundButton = new QPushButton();
    newSoundButton->setFixedSize(150, 75);
    newSoundButton->setText("New Sound");
    newSoundButton->setShortcut(QKeySequence("N"));
    hBoxes.back()->addWidget(newSoundButton);
    connect(newSoundButton, SIGNAL(clicked()), this, SLOT(newSoundClicked()));

    // adds Frame for control buttons
    bottomFrame = new QFrame(window);
    bottomFrame->setGeometry(0, 400, 800, 400);
    bottomFrame->setFixedSize(800, 200);

    // adds VBox for control buttons
    vBox2 = new QVBoxLayout(bottomFrame);
    vBox2->setContentsMargins(4, 4, 4, 4);
    vBox2->setSpacing(4);

    // adds HBox for control buttons
    hBox = new QHBoxLayout();
    hBox->setContentsMargins(4, 4, 4, 4);
    hBox->setSpacing(4);
    vBox2->addLayout(hBox);

    // adds HBox for control buttons
    hBox2 = new QHBoxLayout();
    hBox2->setContentsMargins(4, 4, 4, 4);
    hBox2->setSpacing(4);
    vBox2->addLayout(hBox2);

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
    recordButton->setText("Record Soundboard");
    recordButton->setCheckable(true);
    hBox->addWidget(recordButton);
    connect(recordButton, SIGNAL(clicked()), this, SLOT(recordClicked()));

    // sets shortcut
    QShortcut *shortcut_r = new QShortcut(recordButton);
    shortcut_r->setKey(QKeySequence("r"));
    connect(shortcut_r, SIGNAL(activated()), recordButton, SLOT(click()));

    // adds mic button to HBox
    micButton = new QPushButton();
    micButton->setFixedSize(150, 75);
    micButton->setText("Record Microphone");
    micButton->setCheckable(true);
    hBox->addWidget(micButton);
    connect(micButton, SIGNAL(clicked()), this, SLOT(micClicked()));

    // sets shortcut
    QShortcut *shortcut_m = new QShortcut(micButton);
    shortcut_m->setKey(QKeySequence("m"));
    connect(shortcut_m, SIGNAL(activated()), micButton, SLOT(click()));

    // adds undo button to HBox 2
    undoButton = new QPushButton();
    undoButton->setFixedSize(150, 75);
    undoButton->setText("Undo");
    undoButton->setShortcut(QKeySequence("u"));
    hBox2->addWidget(undoButton);
    connect(undoButton, SIGNAL(clicked()), this, SLOT(undoClicked()));

    // adds save button to HBox 2
    saveButton = new QPushButton();
    saveButton->setFixedSize(150, 75);
    saveButton->setText("Save");
    saveButton->setShortcut(QKeySequence("s"));
    hBox2->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveClicked()));

    // sets up window
    setCentralWidget(window);
    window->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAudioManager(AudioManager *audioManager)
{
    this->audioManager = audioManager;
}

// New Sound Button functionality - opens dialog for new sound file, adds sound button and adjusts
void MainWindow::newSoundClicked()
{
    // sets up file dialog
    QFileDialog *dialog = new QFileDialog;
    dialog->setAcceptMode(QFileDialog::AcceptOpen);
    dialog->setFileMode(QFileDialog::ExistingFile);
    dialog->setViewMode(QFileDialog::List);
    dialog->setNameFilter(tr("Waveform Audio File (*.wav)"));

    // if a valid file is selected, create new sound and new sound button and adjusts
    if (dialog->exec()) {
        audioManager->addSound(new QFile(dialog->selectedFiles().at(0)));

        hBoxes.back()->removeWidget(newSoundButton);

        // adds newButton
        int index = (hBoxes.size() - 2) * 4 + hBoxes.back()->count() - 2;
        QPushButton *newButton = new QPushButton();
        newButton->setFixedSize(150, 75);
        newButton->setText("Custom Sound " + QString::number(index));
        newButton->setShortcut(QKeySequence("F" + QString::number(index)));
        hBoxes.back()->addWidget(newButton);
        connect(newButton, SIGNAL(clicked()), this, SLOT(soundButtonClicked()));

        // creates new HBox if necessary and possible
        if (hBoxes.size() < 4 && hBoxes.back()->count() == 4) {
            hBoxes.push_back(new QHBoxLayout());
            hBoxes.back()->setContentsMargins(4, 4, 4, 4);
            hBoxes.back()->setSpacing(4);
            vBox->addLayout(hBoxes.back());
        }

        // adds newSoundButton back if possible, disables it otherwise
        if (hBoxes.size() <= 4 && hBoxes.back()->count() < 4) {
            hBoxes.back()->addWidget(newSoundButton);
        } else {
            newSoundButton->setEnabled(false);
        }
    }
}

// Play Button functionality - play or pause track
void MainWindow::playClicked()
{
    if (playButton->text().compare(QString("Play")) == 0) {
        playButton->setText("Pause");

        audioManager->play();
    } else {
        playButton->setText("Play");

        audioManager->pause();
    }
}

// Loop Button functionality - loop the track
void MainWindow::loopClicked()
{
    audioManager->loop();
}

// Record Soundboard Button functionality - records from soundboard
void MainWindow::recordClicked()
{
    if (recordButton->text().compare(QString("Record")) == 0) {
        recordButton->setText("Stop Recording");
    } else {
        recordButton->setText("Record");
    }
}

// Mic Button functionality - records from microphone
void MainWindow::micClicked() {

}

// Undo Button functionality - undoes last layer
void MainWindow::undoClicked() {

}

// Save Button functionality - export track
void MainWindow::saveClicked()
{
    if (!audioManager->getTrack()->exists()) {
        QErrorMessage *errorMessage = new QErrorMessage();
        errorMessage->showMessage("Track does not yet exist");
    } else {
        // sets up file dialog
        QFileDialog *dialog = new QFileDialog;
        dialog->setAcceptMode(QFileDialog::AcceptSave);
        dialog->setFileMode(QFileDialog::AnyFile);
        dialog->setViewMode(QFileDialog::List);
        dialog->setNameFilter(tr("Waveform Audio File (*.wav)"));
        dialog->setDefaultSuffix(".wav");
        dialog->selectFile("export.wav");

        // if user selected a valid destination, copy track to destination
        if (dialog->exec()) {
            qInfo() << dialog->selectedFiles().at(0);
            QFile *file = new QFile(dialog->selectedFiles().at(0));
            file->remove();
            audioManager->getTrack()->copy(dialog->selectedFiles().at(0));
        }
    }
}

// Sound Button functionality - play sound
void MainWindow::soundButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString buttonText = button->text();

    // finds index of sound
    int index = 0;
    if (buttonText.left(3).compare("New")  == 0) {
        index = 6 + buttonText.right(buttonText.length() - 10).toInt();
    } else if (buttonText.compare("(1) Hat") == 0) {
        index = 0;
    } else if (buttonText.compare("(2) Kick") == 0) {
        index = 1;
    } else if (buttonText.compare("(3) Perc 1") == 0) {
        index = 2;
    } else if (buttonText.compare("(4) Perc 2") == 0) {
        index = 3;
    } else if (buttonText.compare("(5) Perc 3") == 0) {
        index = 4;
    } else if (buttonText.compare("(6) Snare 1") == 0) {
        index = 5;
    } else if (buttonText.compare("(7) Snare 2") == 0) {
        index = 6;
    }

    audioManager->playSound(index);
}
