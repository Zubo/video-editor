#include <PLL/VideoEffectImageProvider.hpp>

#include <QImage>

#include <opencv2/opencv.hpp>

VideoEffectImageProvider::VideoEffectImageProvider(AbstractVideoEffect const& videoEffect) :
	QQuickImageProvider(QQuickImageProvider::Image),
	_videoEffect(videoEffect)
{
}

QImage VideoEffectImageProvider::requestImage(const QString&, QSize*, const QSize&)
{
	cv::Mat const mat = _videoEffect.getImageEffect();

	return QImage((unsigned char*)mat.data, mat.cols, mat.rows, QImage::Format_ARGB32);
}
