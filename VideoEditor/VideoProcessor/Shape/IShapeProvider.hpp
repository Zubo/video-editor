#ifndef ISHAPEPROVIDER_H
#define ISHAPEPROVIDER_H

#include <opencv2/opencv.hpp>

class IShapeProvider
{
public:
    virtual ~IShapeProvider() = 0;

public:
    virtual cv::Mat const & getShape() const = 0;
};

#endif // ISHAPEPROVIDER_H
