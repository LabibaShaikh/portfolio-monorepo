#ifndef COSC1076_A3_PIXEL_H
#define COSC1076_A3_PIXEL_H

// minimum and maximum values for pixel
#define PIX_MIN 0
#define PIX_MAX 255
/*                                           */
/* This is an abstract class that describe   */
/* the general concepts of a pixel           */
/*                                           */

/**
 * @class Pixel
 * @brief Abstract base class representing a pixel.
 *
 * The Pixel class provides an interface for accessing and manipulating pixel
 * data. It defines pure virtual functions for getting the brightness of a pixel
 * and accessing a channel value.
 */
class Pixel {
public:
  /**
   * @brief Virtual destructor for the Pixel class.
   *
   * The virtual destructor ensures that the derived classes' destructors are
   * called correctly.
   */
  virtual ~Pixel() = default;

  /**
   * @brief Pure virtual function to get the brightness of a pixel.
   *
   * This function returns the brightness value of the pixel.
   * The brightness value is an unsigned integer.
   *
   * @return The brightness value of the pixel.
   */
  virtual unsigned int getBrightness() const = 0;

  /**
   * @brief Pure virtual function to access a channel value.
   *
   * This function allows accessing and modifying the value of a specific
   * channel of the pixel. The channel is specified by a character.
   *
   * @param channel The character representing the channel to access.
   * @return A reference to the channel value.
   */
  virtual unsigned int &operator[](const char channel) = 0;
};

#endif // COSC1076_A3_PIXEL_H
