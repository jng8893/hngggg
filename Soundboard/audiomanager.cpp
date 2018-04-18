#include "audiomanager.h"
#include <QUrl>
#include <QSoundEffect>

AudioManager::AudioManager()
{
    // sets up Audio Format
    format.setSampleRate(44100);
    format.setChannelCount(2);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    // sets up readTrack
    readTrack = new QFile("readTrack.wav");
    readTrack->open(QIODevice::ReadOnly);

    // sets up writeBuffer


    // sets up writeTrack
    writeTrack = new QFile("writeTrack.wav");
    writeTrack->open(QIODevice::WriteOnly);

    // sets up audioOutput
    audioOutput = new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), format);
    connect(audioOutput, SIGNAL(stateChanged(QAudio::State)),
            this, SLOT (audioOutputStateChanged(QAudio::State)));

    // sets up audioInput
    audioInput = new QAudioInput(QAudioDeviceInfo::defaultInputDevice(), format);
}

AudioManager::~AudioManager() {
    readTrack->close();
    writeTrack->close();
    readTrack->remove();
    writeTrack->remove();
}

bool AudioManager::isPlaying()
{
    return playing;
}

void AudioManager::setRecordingSoundboard(bool recording)
{
    this->recordingSoundboard = recording;
}

bool AudioManager::isRecordingSoundboard()
{
    return recordingSoundboard;
}

void AudioManager::setRecordingMic(bool recording)
{
    this->recordingMic = recording;
}

bool AudioManager::isRecordingMic()
{
    return recordingMic;
}

QFile* AudioManager::getTrack()
{
    return readTrack;
}

// loop track
void AudioManager::loop()
{
    // replace readTrack with writeTrack and resets writeTrack
    readTrack->close();
    writeTrack->close();
    readTrack->remove();
    writeTrack->copy(readTrack->fileName());
    writeTrack->remove();
    readTrack->open(QIODevice::ReadOnly);
    writeTrack->open(QIODevice::WriteOnly);

    audioOutput->stop();
    audioOutput->start();
}

// play track
void AudioManager::play()
{
    playing = true;
    if (audioOutput->state() == QAudio::SuspendedState) {
        audioOutput->resume();
    } else {
        audioOutput->start(readTrack);
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
    // play sound
    QSoundEffect *sound = new QSoundEffect();
    sound->setSource(QUrl::fromLocalFile(sounds[index]->fileName()));
    sound->setLoopCount(1);
    sound->setVolume(1.0f);
    sound->play();

    // if recording, write sound to writeBuffer

}

// manages Audio Output State changes
void AudioManager::audioOutputStateChanged(QAudio::State state)
{
    if (state == QAudio::ActiveState) {
        // start writing readTrack to writeBuffer

        // if recording from mic, start writing to writeBuffer

    } else if (state == QAudio::SuspendedState) {
        // pause writing readTrack to writeBuffer

        // if recording from mic, pause writing to writeBuffer

    } else if (state == QAudio::IdleState) {
        audioOutput->stop();
        readTrack->close();
        readTrack->open(QIODevice::ReadOnly);
        audioOutput->start(readTrack);
    }
}
