#include "linear_blending.h"

cv::Mat linearBlending(const cv::Mat& img_1, const cv::Mat& img_2, const cv::Mat& weights)
{
  // TODO 3.1: Blend the two images according to the weights:
  //   result = img_1 * weights + img_2 * (1-weights)
  // No need to loop through all pixels!
  // Hint: https://docs.opencv.org/4.0.1/d1/d10/classcv_1_1MatExpr.html
 // cv::addWeighted(weights);
  return weights.mul(img_1) + (cv::Scalar(1.0,1.0,1.0) - weights).mul(img_2);
  //return weights*(img_1) + (1.f - weights)*img_2
}
