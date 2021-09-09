#ifndef CONST_H
#define CONST_H

#include <opencv2/opencv.hpp>

class Const
{
public:
	static const cv::Scalar RedColorScalar;
	static const cv::Scalar BlueColorScalar;

private:
    Const() = delete;
};

#endif // CONST_H
