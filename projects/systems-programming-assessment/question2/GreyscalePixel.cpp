#include "GreyscalePixel.h"
#include <cassert>
#include <stdexcept>

// Construct a GreyscalePixel with intensity channels initialized to 0
GreyscalePixel::GreyscalePixel() : intensity(0) {}

// Construct a GreyscalePixel with intensity channels initialized to intensity
GreyscalePixel::GreyscalePixel(unsigned int intensity) : intensity(intensity) {
  // Precondition: intensity must be within valid range
  assert(intensity >= PIX_MIN && intensity <= PIX_MAX);
}

// Destructor
GreyscalePixel::~GreyscalePixel() {}

// Return the brightness of a pixel
// brightness for GreyscalePixel = intensity
unsigned int GreyscalePixel::getBrightness() const {
  // Postcondition: brightness should be equal to intensity
  assert(intensity >= PIX_MIN && intensity <= PIX_MAX);
  return intensity;
}

// Should return a reference to the corresponding channel value of the pixel
// 'i' <- intensity
unsigned int &GreyscalePixel::operator[](const char channel) {
  // Precondition: channel must be 'i' for intensity
  if (channel != 'i') {
    throw std::invalid_argument("Invalid channel");
  }
  // Postcondition: returns a valid reference to intensity
  return intensity;
}
