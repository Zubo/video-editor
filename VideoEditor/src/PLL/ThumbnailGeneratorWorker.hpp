#ifndef THUMBNAILGENERATORWORKER_H
#define THUMBNAILGENERATORWORKER_H

#include <string>

#include <QObject>

#include <BLL/ThumbnailGenerator.hpp>

class ThumbnailGeneratorWorker : public QObject
{
    Q_OBJECT
public:
    ThumbnailGeneratorWorker();
    void registerPath(std::string const& path);
    void registerExtension(std::string const& extension);

public slots:
    void generateThumbnails();
    void abort();

signals:
    void generatingEnded();

private:
    ThumbnailGenerator _thumbnailGenerator;
};

#endif // THUMBNAILGENERATORWORKER_H
