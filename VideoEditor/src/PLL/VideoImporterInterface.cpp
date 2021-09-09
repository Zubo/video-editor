#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QUrl>

#include <PLL/VideoImporterInterface.hpp>

VideoImporterInterface::VideoImporterInterface(std::string const& importDestDirPath) :
	QObject(nullptr),
	_importDestDirPath(importDestDirPath)
{
}

Q_INVOKABLE void VideoImporterInterface::importFiles(QList<QUrl> srcFilePaths)
{
    for (auto const& srcPathQUrl: srcFilePaths) {
        QString const srcPath = srcPathQUrl.toLocalFile();
        QFile srcFile(srcPath);
        QFileInfo const srcFileInfo(srcFile);
        QString const destPath = QString(_importDestDirPath.c_str()) + QString("/") + srcFileInfo.fileName();
        QFile target(destPath);

        if (target.exists()) {
            target.remove();
        }

        if (!srcFile.copy(target.fileName())) {
            emit importingFailed();
            return;
        }
    }

	emit importingFinished();
}
