#include <VideoProcessor/ImageEffect/AbstractVideoEffect.hpp>

#include <vector>

AbstractVideoEffect::~AbstractVideoEffect() = default;

void AbstractVideoEffect::applyToImage(cv::Mat& img, cv::Point2i const pos) const
{
    std::vector<cv::Mat> rgbaLayers;
    
    cv::Mat effect = getImageEffect();
    cv::split(effect, rgbaLayers);
    cv::Mat rgbLayers[3] = { rgbaLayers[0], rgbaLayers[1], rgbaLayers[2] };

    // Alpha to mask
    cv::Mat mask = rgbaLayers[3];
    cv::Mat effectRgb;
    merge(rgbLayers, 3, effectRgb);

	cv::Mat outputRange = img.rowRange(pos.y, effect.rows + pos.y).colRange(pos.x, effect.cols + pos.x);
    effectRgb.copyTo(outputRange, mask);


    /*cv::Mat effectImg;
    getImageEffect().convertTo(effectImg, img.type());
    cv::Mat range = img.rowRange(pos.y, effectImg.rows + pos.y).colRange(pos.x, effectImg.cols + pos.x);
    cv::Mat outputImg(effectImg.rows, effectImg.cols, range.type());
    cv::add(range, effectImg, outputImg);*/
}
