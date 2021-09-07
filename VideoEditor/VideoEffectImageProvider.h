#ifndef VIDEOEFFECTIMAGEPROVIDER_H
#define VIDEOEFFECTIMAGEPROVIDER_H


#include <QQuickImageProvider>

#include <VideoProcessor/ImageEffect/AbstractVideoEffect.hpp>

class VideoEffectImageProvider : public QQuickImageProvider
{
public:
	VideoEffectImageProvider(AbstractVideoEffect const & imageEffectProvider);

public:
	QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;

signals:


private:
	AbstractVideoEffect const & _imageEffectProvider;
};

#endif // VIDEOEFFECTIMAGEPROVIDER_H
