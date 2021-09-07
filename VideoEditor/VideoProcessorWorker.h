#ifndef VIDEOPROCESSORQTHREAD_H
#define VIDEOPROCESSORQTHREAD_H

#include <string>

#include <QObject>

class VideoProcessorWorker : public QObject
{
    Q_OBJECT
public:
    VideoProcessorWorker();

public slots:
	void processVideo();

public:
    void stop();

signals:
    void progressChanged(float val);
    void finished();

private:
    std::string _sourceFilePath;
    std::string _destinationFilePath;
    bool _stop = true;
};

#endif // VIDEOPROCESSORQTHREAD_H
