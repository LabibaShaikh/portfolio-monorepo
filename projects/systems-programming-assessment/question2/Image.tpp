#ifndef COSC1076_A3_IMAGE_TPP
#define COSC1076_A3_IMAGE_TPP

#include "Image.h"

template <typename PixelType>
Image<PixelType>::Image(int nRows, int nCols)
    : img(nRows, std::vector<PixelType>(nCols)) {
  // Precondition: nRows and nCols must be positive integers
  assert(nRows > 0 && nCols > 0);
}

template <typename PixelType> Image<PixelType>::~Image() {}

template <typename PixelType>
PixelType Image<PixelType>::get(int row, int col) const {
  // Precondition: row and col must be within the bounds of the image
  if (row < 0 || static_cast<size_t>(row) >= img.size() || col < 0 ||
      static_cast<size_t>(col) >= img[0].size()) {
    throw std::out_of_range("Pixel coordinates out of range");
  }
  // Postcondition: Returns the pixel at the specified location
  return img[row][col];
}

template <typename PixelType>
void Image<PixelType>::set(int row, int col, const PixelType &pix) {
  // Precondition: row and col must be within the bounds of the image
  if (row < 0 || static_cast<size_t>(row) >= img.size() || col < 0 ||
      static_cast<size_t>(col) >= img[0].size()) {
    throw std::out_of_range("Pixel coordinates out of range");
  }
  // Postcondition: The pixel at the specified location is set to pix
  img[row][col] = pix;
}

#endif // COSC1076_A3_IMAGE_TPP
