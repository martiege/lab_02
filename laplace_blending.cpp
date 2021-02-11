#include "laplace_blending.h"
#include "linear_blending.h"
#include "opencv2/imgproc.hpp"

#include <iostream>

cv::Mat laplaceBlending(const cv::Mat& img_1, const cv::Mat& img_2, const cv::Mat& weights)
{
  // Construct a gaussian pyramid of the weight image.
  // TODO 4.1: Finish constructGaussianPyramid().
  std::vector<cv::Mat> weights_pyr = constructGaussianPyramid(weights);

  // Construct a laplacian pyramid of each of the images.
  // TODO 4.2: Finish constructLaplacianPyramid().
  std::vector<cv::Mat> img_1_pyr = constructLaplacianPyramid(img_1);
  std::vector<cv::Mat> img_2_pyr = constructLaplacianPyramid(img_2);

  // Blend the laplacian pyramids according to the corresponding weight pyramid.
  std::vector<cv::Mat> blend_pyr(img_1_pyr.size());
  for (size_t i = 0; i < img_1_pyr.size(); ++i)
  {
    // TODO 4.3: Blend the images using linearBlending() on each pyramid level.
    blend_pyr[i] = linearBlending(img_1_pyr[i], img_2_pyr[i], weights_pyr[i]); 
  }

  // TODO 4.4: Collapse the blended laplacian pyramid.
  return collapsePyramid(blend_pyr);
}

std::vector<cv::Mat> constructGaussianPyramid(const cv::Mat& img)
{
  // Construct the pyramid starting with the original image.
  std::vector<cv::Mat> pyr;
  pyr.push_back(img.clone());

  // Add new downscaled images to the pyramid
  // until image width is <= 16 pixels
  while(pyr.back().cols > 16)
  {
    // TODO 4.1.a: Add the next level in the pyramid.
    // Hint cv::pyrDown(...)
    cv::Mat down; 
    cv::pyrDown(pyr.back(), down);
    pyr.push_back(down.clone()); 
    // break; // TODO 4.1.b: Remove this break! (Why did I have to add this now? No change in pyr.back, so no change in pyr.back.cols. inf loop)
  }

  return pyr;
}

std::vector<cv::Mat> constructLaplacianPyramid(const cv::Mat& img)
{
  // TODO 4.2.a: Use constructGaussianPyramid() to construct a laplacian pyramid.
  // Hint: cv::pyrUp(...)
  std::vector<cv::Mat> pyr = constructGaussianPyramid(img);
  for (std::size_t i{0}; i < pyr.size() - 1; ++i)
  {
    cv::Mat up; 
    cv::pyrUp(pyr[i + 1], up, pyr[i].size()); 
    pyr[i] = pyr[i] - up; 
  }

  return pyr;
}

cv::Mat collapsePyramid(const std::vector<cv::Mat>& pyr)
{
  // TODO 4.4.a: Collapse the pyramid.
  cv::Mat collapsed = pyr.back().clone();
  for (long int i{static_cast<long int>(pyr.size()) - 2}; i >= 0; --i)
  {
    cv::Mat local; 
    cv::pyrUp(collapsed, local, pyr[i].size()); 
    collapsed = local + pyr[i]; 
  }

  return collapsed;
}


void printLength(const std::vector<cv::Mat>& pyr){
for (long int i=0;i<static_cast<long int>(pyr.size());i++){
  std::cout <<pyr[i].size()<<std::endl;
}
}





