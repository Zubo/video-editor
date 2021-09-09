#ifndef VIDEOEFFECTIMAGEPROVIDER_H
#define VIDEOEFFECTIMAGEPROVIDER_H


#include <QQuickImageProvider>

#include <BLL/VideoProcessor/VideoEffect/AbstractVideoEffect.hpp>

class VideoEffectImageProvider : public QQuickImageProvider
{
public:
	VideoEffectImageProvider(AbstractVideoEffect const& videoEffect);

public:
	QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;

private:
	AbstractVideoEffect const & _videoEffect;
};

#endif // VIDEOEFFECTIMAGEPROVIDER_H
