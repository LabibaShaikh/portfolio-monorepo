#include "RGBPixel.h"
#include <stdexcept>

// Construct a RGBPixel with all channels initialized to 0
RGBPixel::RGBPixel() : r(0), g(0), b(0) {}

// Construct a RGBPixel with all channels initialized to r, g, b
RGBPixel::RGBPixel(unsigned int r, unsigned int g, unsigned int b)
    : r(r), g(g), b(b) {
  // Precondition: r, g, b must be within valid range
  assert(r >= PIX_MIN && r <= PIX_MAX);
  assert(g >= PIX_MIN && g <= PIX_MAX);
  assert(b >= PIX_MIN && b <= PIX_MAX);
}

// Destructor
RGBPixel::~RGBPixel() {}

// Return the brightness of a pixel
// brightness for RGBPixel = (r + g + b) / 3
unsigned int RGBPixel::getBrightness() const {
  // Postcondition: brightness should be within valid range
  unsigned int brightness = (r + g + b) / 3;
  assert(brightness >= PIX_MIN && brightness <= PIX_MAX);
  return brightness;
}

// Should return a reference to the corresponding channel value of the pixel
// 'r' <- red channel
// 'g' <- green channel
// 'b' <- blue channel
unsigned int &RGBPixel::operator[](const char channel) {
  // Precondition: channel must be 'r', 'g', or 'b'
  if (channel == 'r') {
    return r;
  } else if (channel == 'g') {
    return g;
  } else if (channel == 'b') {
    return b;
  } else {
    throw std::invalid_argument("Invalid channel");
  }
}
