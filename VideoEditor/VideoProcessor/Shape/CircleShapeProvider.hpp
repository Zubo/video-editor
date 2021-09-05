#ifndef CIRCLESHAPEPROVIDER_HPP
#define CIRCLESHAPEPROVIDER_HPP

#include <VideoProcessor/Shape/IShapeProvider.hpp>

class CircleShapeProvider : public IShapeProvider
{
public:
    static CircleShapeProvider create(int const radius, cv::Scalar const & colorScalar);

private:
    CircleShapeProvider(int const radius);

public:
    cv::Mat const & getShape() const override;

private:
    cv::Mat _shape;
};

#endif // CIRCLESHAPEPROVIDER_HPP
