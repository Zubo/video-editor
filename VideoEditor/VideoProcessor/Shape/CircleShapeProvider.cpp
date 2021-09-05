#include "CircleShapeProvider.hpp"

#include <opencv2/opencv.hpp>

CircleShapeProvider CircleShapeProvider::create(int const radius, cv::Scalar const & colorScalar)
{
    CircleShapeProvider circleShapeProvider{ radius };
    cv::Point const center{ radius, radius };
    cv::circle(circleShapeProvider._shape, center, radius, colorScalar);

    return circleShapeProvider;
}

CircleShapeProvider::CircleShapeProvider(int const radius) :
    _shape(radius * 2, radius * 2, CV_8UC4, cv::Scalar::all(0))
{
}

cv::Mat const & CircleShapeProvider::getShape() const
{
    return _shape;
}
