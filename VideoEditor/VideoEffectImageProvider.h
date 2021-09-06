#ifndef VIDEOEFFECTIMAGEPROVIDER_H
#define VIDEOEFFECTIMAGEPROVIDER_H


#include <QQuickImageProvider>

#include <VideoProcessor/ImageEffect/IImageEffectProvider.hpp>

class VideoEffectImageProvider : public QQuickImageProvider
{
public:
	VideoEffectImageProvider(IImageEffectProvider const & imageEffectProvider);

public:
	QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;

private:
	IImageEffectProvider const & _imageEffectProvider;
};

#endif // VIDEOEFFECTIMAGEPROVIDER_H
