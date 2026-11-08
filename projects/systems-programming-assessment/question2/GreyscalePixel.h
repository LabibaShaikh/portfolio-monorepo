#ifndef COSC1076_A3_GREYSCALE_PIXEL_H
#define COSC1076_A3_GREYSCALE_PIXEL_H

#include "Pixel.h"

/**
 * @class GreyscalePixel
 * @brief Represents a pixel with greyscale intensity.
 *
 * The GreyscalePixel class is a subclass of the Pixel class and represents a
 * pixel with greyscale intensity. It stores the intensity value of the pixel
 * and provides methods to access and modify the intensity.
 */
class GreyscalePixel : public Pixel {
public:
  /**
   * @brief Constructs a GreyscalePixel with intensity channels initialized to
   * 0.
   */
  GreyscalePixel();

  /**
   * @brief Constructs a GreyscalePixel with intensity channels initialized to
   * the specified intensity.
   * @param intensity The intensity value to initialize the pixel with.
   */
  GreyscalePixel(unsigned int intensity);

  /**
   * @brief Destructor for the GreyscalePixel class.
   */
  ~GreyscalePixel();

  /**
   * @brief Returns the brightness of the pixel.
   * @return The brightness of the pixel, which is equal to the intensity value.
   */
  unsigned int getBrightness() const override;

  /**
   * @brief Returns a reference to the corresponding channel value of the pixel.
   * @param channel The channel to access. In the case of GreyscalePixel, 'i'
   * represents intensity.
   * @return A reference to the intensity channel value of the pixel.
   */
  unsigned int &operator[](const char channel) override;

private:
  /*                                           */
  /* DO NOT MODIFY ANY CODE IN THIS SECTION     */
  /*                                           */

  unsigned int intensity; // intensity channel value
};

#endif // COSC1076_A3_GREYSCALE_PIXEL_H
