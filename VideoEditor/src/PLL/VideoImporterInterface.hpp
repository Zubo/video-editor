#ifndef VIDEOIMPORTERINTERFACE_HPP
#define VIDEOIMPORTERINTERFACE_HPP

#include <optional>
#include <string>

#include <QList>
#include <QObject>
#include <QString>
#include <QVariant>

class VideoImporterInterface : public QObject
{
    Q_OBJECT

public:
    VideoImporterInterface(std::string const& importDestDirPath);

public:
    Q_INVOKABLE void importFiles(QList<QUrl>);

signals:
    void importingFinished();
    void importingFailed();

private:
    std::string _importDestDirPath;
};

#endif // VIDEOIMPORTERINTERFACE_HPP
