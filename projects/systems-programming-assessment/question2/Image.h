#ifndef COSC1076_A3_IMAGE_H
#define COSC1076_A3_IMAGE_H

#include <stdexcept>
#include <vector>

#include "GreyscalePixel.h"
#include "Pixel.h"
#include "RGBPixel.h"

template <typename PixelType> class Image {
public:
  /**
   * Construct an image with nRows (number of rows) and nCols (number of
   * columns)
   * @param nRows The number of rows in the image
   * @param nCols The number of columns in the image
   */
  Image(int nRows, int nCols);

  /**
   * Destructor: should clear the image
   */
  ~Image();

  /**
   * Get the pixel (RGBPixel or GreyscalePixel) at [row, col]
   * @param row The row index of the pixel
   * @param col The column index of the pixel
   * @return The pixel at the specified location
   * @throws std::out_of_range if row or col is out of bounds
   */
  PixelType get(int row, int col) const;

  /**
   * Set the pixel at (row, col) to pix
   * @param row The row index of the pixel
   * @param col The column index of the pixel
   * @param pix The pixel to set at the specified location
   * @throws std::out_of_range if row or col is out of bounds
   */
  void set(int row, int col, const PixelType &pix);

private:
  // Should be a vector of vectors
  std::vector<std::vector<PixelType>> img;
};

#include "Image.tpp"

#endif // COSC1076_A3_IMAGE_H
