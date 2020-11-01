#include "ImageIO.h"

#include <stdexcept>

#include "IyathuumCoreLib/BaseTypes/Color.h"
#include "../Lib/lodepng/lodepng.h"

namespace YolonaOss {
  ImageIO::ImageIO()
  {
  }


  ImageIO::~ImageIO()
  {
  }

  void ImageIO::writeImage(std::string filename, const Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2> & img){

    size_t width = img.getDimension(0);
    size_t height = img.getDimension(1);
    std::vector<unsigned char> image;
    image.resize(width * height * 4);
    for (unsigned y = 0; y < height; y++)
      for (unsigned x = 0; x < width; x++) {
        Iyathuum::Color& c = img.getVal(x, y);
        image[4 * width * y + 4 * x + 0] = (unsigned char)c.r();
        image[4 * width * y + 4 * x + 1] = (unsigned char)c.g();
        image[4 * width * y + 4 * x + 2] = (unsigned char)c.b();
        image[4 * width * y + 4 * x + 3] = (unsigned char)c.a();
      }

    unsigned error = lodepng::encode(filename.c_str(), image, (unsigned int)width, (unsigned int)height);
    if (error)
      throw std::runtime_error("encoder error " + std::to_string(error) + ": " + lodepng_error_text(error) + "\n");
  }

  std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> ImageIO::readImage(std::string filename) {
    std::string extension = ".dds";
    std::transform(filename.begin(), filename.end(), filename.begin(),
      [](unsigned char c) { return std::tolower(c); });
    if (std::equal(extension.rbegin(), extension.rend(), filename.rbegin()))
      return std::move(readDDS(filename));
    else
      return std::move(readPNG(filename));
  }
  
  std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> ImageIO::readPNG(std::string filename){
    std::vector<unsigned char> image; //the raw pixels
    unsigned int width, height;

    //decode
    unsigned error = lodepng::decode(image, width, height, filename);

    //if there's an error, display it
    if (error) throw std::runtime_error("decoder error " + std::to_string(error) + ": " + lodepng_error_text(error) + "\n");

    std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> result = std::make_unique<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>(width, height);

    for (unsigned y = 0; y < height; y++)
      for (unsigned x = 0; x < width; x++) {
        Iyathuum::Color& c = result->getRef(x, y);
        c.r() = image[4 * width * y + 4 * x + 0];
        c.g() = image[4 * width * y + 4 * x + 1];
        c.b() = image[4 * width * y + 4 * x + 2];
        c.a() = image[4 * width * y + 4 * x + 3];
      }
    return result;
  }

  void ImageIO::TEST_readwrite() {
    auto s = ImageIO::readImage("Test/ImageIO.png");
    ImageIO::writeImage("Test/ImageIO2.png", *s);
  }

  void ImageIO::TEST_createNew() {
    size_t width = 512;
    size_t height = 512;
    Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2> m(width, height);
    for (int x = 0; x < width; x++)
      m.getRef(x, 0) = Iyathuum::Color(0, 0, 255);
    for (int y = 0; y < height; y++)
      m.getRef(0, y) = Iyathuum::Color(255, 255, 255);
    ImageIO::writeImage("Test/ImageIO.png", m);
  }

  std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> ImageIO::readDDS(std::string filename)
  {
    return nullptr;
  }
}