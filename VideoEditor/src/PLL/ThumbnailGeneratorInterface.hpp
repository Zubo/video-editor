#ifndef THUMBNAILGENERATORINTERFACE_HPP
#define THUMBNAILGENERATORINTERFACE_HPP

#include <optional>

#include <QObject>
#include <QThread>

#include <PLL/BLLContext.hpp>
#include <PLL/ThumbnailGeneratorWorker.hpp>

class ThumbnailGeneratorInterface : public QObject
{
    Q_OBJECT

public:
    ThumbnailGeneratorInterface(BLLContext& bllContext);
	virtual ~ThumbnailGeneratorInterface();

signals:
	void generatingEnded();

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
