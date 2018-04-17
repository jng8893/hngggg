#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QFile>
#include <QAudioOutput>
#include <QAudioRecorder>
#include <vector>

class AudioManager : public QObject
{
    Q_OBJECT

public:
    AudioManager();
    ~AudioManager();

    bool isPlaying();
    void setRecording(bool recording);
    bool isRecording();

    QFile* getTrack();
    void play();
    void pause();
    void loop();

    void addSound(QFile *file);
    void playSound(int index);

private:
    QAudioFormat format;
    QAudioOutput *audioOutput;
    QAudioRecorder *audioRecorder;

    bool playing;
    bool recording;

    QFile *readTrack;
    QFile *writeTrack;

    std::vector<QFile*> sounds;

private slots:
    void audioOutputStateChanged(QAudio::State);
};

#endif // AUDIOMANAGER_H
