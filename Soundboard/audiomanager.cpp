#include "audiomanager.h"
#include <QUrl>


AudioManager::AudioManager(QWidget *parent)
{
    // sets up Audio Format
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    // sets up readTrack
    readTrack = new QFile("readTrack.wav");
    readTrack->open(QIODevice::ReadOnly);

    // sets up writeTrack
    writeTrack = new QFile("writeTrack.amr");
    writeTrack->open(QIODevice::WriteOnly);

    // sets up audioOutput
    audioOutput = new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), format);
    connect(audioOutput, SIGNAL(stateChanged(QAudio::State)),
            this, SLOT (audioOutputStateChanged(QAudio::State)));

    // sets up Audio Encoder Settings
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/amr");
    audioSettings.setQuality(QMultimedia::HighQuality);

    // sets up audioRecorder
    audioRecorder = new QAudioRecorder;
    audioRecorder->setEncodingSettings(audioSettings);
    audioRecorder->setOutputLocation(QUrl::fromLocalFile(writeTrack->fileName()));
    audioRecorder->setAudioInput(audioRecorder->defaultAudioInput());
}

bool AudioManager::isPlaying()
{
    return playing;
}

void AudioManager::setRecording(bool recording) {
    this->recording = recording;
}

bool AudioManager::isRecording() {
    return recording;
}

QFile* AudioManager::getTrack() {
    return readTrack;
}

// loop track
void AudioManager::loop() {
    audioOutput->reset();
}

// play track
void AudioManager::play() {
    playing = true;
    if (audioOutput->state() == QAudio::SuspendedState) {
        audioOutput->resume();
    } else {
        audioOutput->start();
    }
}

// pause track
void AudioManager::pause() {
    playing = false;
    audioOutput->suspend();
}

// add sound file to sounds vector
void AudioManager::addSound(QFile *file) {
    sounds.push_back(file);
}

// play the sound at sounds[index] and sound is added to track if recording, use audioOutput
void AudioManager::playSound(int index) {
    sounds[index]->open(QIODevice::ReadOnly);
    QAudioOutput newAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), format);
    newAudioOutput.start(sounds[index]);
//    sounds[index]->close();
}

// manages Audio Output State changes, see http://doc.qt.io/qt-5/qaudiooutput.html
void AudioManager::audioOutputStateChanged(QAudio::State) {

}
