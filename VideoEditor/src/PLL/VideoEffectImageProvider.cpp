#include <PLL/VideoEffectImageProvider.h>

#include <QImage>

#include <opencv2/opencv.hpp>

VideoEffectImageProvider::VideoEffectImageProvider(AbstractVideoEffect const& imageEffectProvider) :
	QQuickImageProvider(QQuickImageProvider::Image),
	_imageEffectProvider(imageEffectProvider)
{
}

QImage VideoEffectImageProvider::requestImage(const QString&, QSize*, const QSize&)
{
	cv::Mat const mat = _imageEffectProvider.getImageEffect();

	return QImage((unsigned char*)mat.data, mat.cols, mat.rows, QImage::Format_ARGB32);
}
