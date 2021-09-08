#include <VideoProcessor/ImageEffect/AbstractVideoEffect.hpp>

#include <vector>

AbstractVideoEffect::~AbstractVideoEffect() = default;

void AbstractVideoEffect::applyToImage(cv::Mat& img, cv::Point2i const pos) const
{
    if (pos.x > img.rows - 2 && pos.y > img.rows - 2) {
        // The effect's position is out of bounds
        return;
    }

    std::vector<cv::Mat> rgbaLayers;
    
    cv::Mat effect = getImageEffect();
    cv::split(effect, rgbaLayers);
    cv::Mat rgbLayers[3] = { rgbaLayers[0], rgbaLayers[1], rgbaLayers[2] };

    // Alpha to mask
    cv::Mat mask = rgbaLayers[3];
    cv::Mat effectRgb;
    merge(rgbLayers, 3, effectRgb);

    int const outputRowMin = std::min(pos.y, img.rows);
    int const outputRowMax = std::min(effect.rows + pos.y, img.rows);
    int const inputColMin =  std::min(pos.x, img.cols);
    int const intputColMax = std::min(effect.cols + pos.x, img.cols);
	cv::Mat outputRange = img
        .rowRange(outputRowMin, outputRowMax)
        .colRange(inputColMin, intputColMax);

    int const effectOutputRowMax = std::min(effectRgb.rows, outputRange.rows);
    int const effectOutputColMax = std::min(effectRgb.cols, outputRange.cols);
    cv::Mat effectRange = effectRgb
        .rowRange(0, effectOutputRowMax)
        .colRange(0, effectOutputColMax);
    cv::Mat maskRange = effectRange
            .rowRange(0, effectOutputRowMax)
            .colRange(0, effectOutputColMax);
    effectRange.copyTo(outputRange, maskRange);
}
