#include "audiomanager.h"
#include <QUrl>
#include <QSound>

AudioManager::AudioManager()
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

AudioManager::~AudioManager() {
    readTrack->close();
    writeTrack->close();
}

bool AudioManager::isPlaying()
{
    return playing;
}

void AudioManager::setRecording(bool recording)
{
    this->recording = recording;
}

bool AudioManager::isRecording()
{
    return recording;
}

QFile* AudioManager::getTrack()
{
    return readTrack;
}

// loop track
void AudioManager::loop()
{
    audioOutput->reset();
}

// play track
void AudioManager::play()
{
    playing = true;
    if (audioOutput->state() == QAudio::SuspendedState) {
        audioOutput->resume();
    } else {
        audioOutput->start();
    }
}

// pause track
void AudioManager::pause()
{
    playing = false;
    audioOutput->suspend();
}

// add sound file to sounds vector
void AudioManager::addSound(QFile *file)
{
    sounds.push_back(file);
}

// play the sound at sounds[index] and sound is added to track if recording
void AudioManager::playSound(int index)
{
    QSound::play(sounds[index]->fileName());
    // if recording, add to track
}

// manages Audio Output State changes
void AudioManager::audioOutputStateChanged(QAudio::State state)
{
    // blah blah.close();
    if (state == QAudio::StoppedState) {
        qt_error_string();
    }
}
