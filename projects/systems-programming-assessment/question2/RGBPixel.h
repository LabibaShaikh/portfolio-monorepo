#ifndef COSC1076_A3_RGB_PIXEL_H
#define COSC1076_A3_RGB_PIXEL_H
#include "Pixel.h"
#include <cassert>

/**
 * @class RGBPixel
 * @brief Represents a pixel with red, green, and blue channels.
 *
 * The RGBPixel class is a subclass of the Pixel class and represents a pixel
 * with red, green, and blue channels. It provides methods to construct an
 * RGBPixel with channel values, get the brightness of the pixel, and access the
 * individual channel values.
 */
class RGBPixel : public Pixel {
public:
  /**
   * @brief Constructs an RGBPixel with all channels initialized to 0.
   */
  RGBPixel();

  /**
   * @brief Constructs an RGBPixel with the specified channel values.
   * @param r The red channel value.
   * @param g The green channel value.
   * @param b The blue channel value.
   */
  RGBPixel(unsigned int r, unsigned int g, unsigned int b);

  /**
   * @brief Destructor for the RGBPixel class.
   */
  ~RGBPixel();

  /**
   * @brief Returns the brightness of the pixel.
   * @return The brightness of the pixel calculated as (r + g + b) / 3.
   */
  unsigned int getBrightness() const override;

  /**
   * @brief Returns a reference to the corresponding channel value of the pixel.
   * @param channel The channel to access ('r' for red, 'g' for green, 'b' for
   * blue).
   * @return A reference to the channel value.
   */
  unsigned int &operator[](const char channel) override;

private:
  /*                                           */
  /* DO NOT MODIFY ANY CODE IN THIS SECTION     */
  /*                                           */

  unsigned int r; // red channel value
  unsigned int g; // green channel value
  unsigned int b; // blue channel value
};

#endif // COSC1076_A3_RGB_PIXEL_HF