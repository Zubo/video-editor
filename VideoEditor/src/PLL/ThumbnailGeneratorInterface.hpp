#ifndef THUMBNAILGENERATORINTERFACE_HPP
#define THUMBNAILGENERATORINTERFACE_HPP

#include <optional>

#include <QObject>
#include <QThread>

#include <PLL/BLLContext.h>
#include <PLL/ThumbnailGeneratorWorker.h>

class ThumbnailGeneratorInterface : public QObject
{
    Q_OBJECT

public:
    ThumbnailGeneratorInterface(BLLContext& bllContext);
	virtual ~ThumbnailGeneratorInterface();

public slots:
	void requestThumbnailGeneration();

private:
	void stopGenerating();

private slots:
	void waitForThumbnailGeneratorThreadToFinish();

private:
	std::optional<QThread> _thumbnailGeneratorThread;
	std::optional<ThumbnailGeneratorWorker> _thumbnailGeneratorWorkerObject;
	BLLContext& _bllContext;
};

#endif // THUMBNAILGENERATORINTERFACE_HPP
