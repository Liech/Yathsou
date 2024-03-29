#include "ImageIO.h"

#include <stdexcept>

#include "IyathuumCoreLib/BaseTypes/Color.h"
#include <lodepng.h>
#include <gli/load_dds.hpp>
#include <gli/texture2d.hpp>
#include <gli/texture_cube.hpp>
#include <gli/sampler2d.hpp>
#include <fstream>

namespace Aezesel {
  ImageIO::ImageIO()
  {
  }


  ImageIO::~ImageIO()
  {
  }

  void ImageIO::writeImage(const std::string& filename, const Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2> & img){

    size_t width = img.getDimension(0);
    size_t height = img.getDimension(1);
    std::vector<unsigned char> image;
    image.resize(width * height * 4);
    for (unsigned y = 0; y < height; y++)
      for (unsigned x = 0; x < width; x++) {
        Iyathuum::Color c = img.getVal(x, y);
        image[4 * width * y + 4 * x + 0] = (unsigned char)c.r();
        image[4 * width * y + 4 * x + 1] = (unsigned char)c.g();
        image[4 * width * y + 4 * x + 2] = (unsigned char)c.b();
        image[4 * width * y + 4 * x + 3] = (unsigned char)c.a();
      }

    unsigned error = lodepng::encode(filename.c_str(), image, (unsigned int)width, (unsigned int)height);
    if (error)
      throw std::runtime_error("encoder error " + std::to_string(error) + ": " + lodepng_error_text(error) + "\n");
  }

  std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> ImageIO::readImage(const std::string& inputFilename) {
    std::string filename = inputFilename;
    std::string extension = ".dds";
    std::transform(filename.begin(), filename.end(), filename.begin(),
      [](unsigned char c) { return std::tolower(c); });
    if (std::equal(extension.rbegin(), extension.rend(), filename.rbegin()))
      return std::move(readDDS(filename));
    else
      return std::move(readPNG(filename));
  }
  
  std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>  ImageIO::readImage(ImageIO::Format format,const std::vector<unsigned char>& data) {
    if (format == Format::DDS)
      return std::move(readDDS(data));
    else
      return std::move(readPNG(data));
  }

  std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> ImageIO::readPNG(const std::string& filename) {
    std::vector<unsigned char> image; //the raw pixels
    unsigned int width, height;

    unsigned error = lodepng::decode(image, width, height, filename);

    if (error)
      throw std::runtime_error("decoder error " + std::to_string(error) + ": " + lodepng_error_text(error) + "\n");
    return std::move(readPNG(width, height, image));
  }


  std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> ImageIO::readPNG(const std::vector<unsigned char>& data) {
    std::vector<unsigned char> image; //the raw pixels
    unsigned int width, height;

    unsigned error = lodepng::decode(image, width, height, data);
    if (error)
      throw std::runtime_error("decoder error " + std::to_string(error) + ": " + lodepng_error_text(error) + "\n");
    return std::move(readPNG(width, height, image));
  }

  std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> ImageIO::readPNG(int width, int height, std::vector<unsigned char>& image) {
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

  std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> ImageIO::readDDS(const std::string& filename)
  {
    gli::texture texture = gli::load_dds(filename);
    gli::texture2d texture2d = gli::texture2d(texture);
    return std::move(readDDS(texture2d));
  }

  std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> ImageIO::readDDS(const std::vector<unsigned char>& data)
  {
    gli::texture texture = gli::load_dds((char const*)(data.data()), data.size());
    gli::texture2d texture2d = gli::texture2d(texture);
    return std::move(readDDS(texture2d));
  }

  bool ImageIO::isDDSCube(const std::string& filename) {
    gli::texture texture = gli::load_dds(filename);
    return texture.faces() > 1;
  }

  bool ImageIO::isDDSCube(const std::vector<unsigned char>& data) {
    gli::texture texture = gli::load_dds((char const*)(data.data()), data.size());
    return texture.faces() > 1;
  }

  std::vector<std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>> ImageIO::readDDSCube(const std::string& filename) {
    gli::texture texture = gli::load_dds(filename);
    std::vector<std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>> result;
    gli::texture_cube cube = gli::texture_cube(texture);
    result.resize(texture.faces());
    for (int i = 0; i < texture.faces(); i++) {      
      const gli::texture2d tex = cube[i];
      result[i] = std::move(readDDS(tex));
    }
    return result;
  }

  std::vector<std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>> ImageIO::readDDSCube(ImageIO::Format, const std::vector<unsigned char>& data) {
    gli::texture texture = gli::load_dds((char const*)(data.data()), data.size());
    std::vector<std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>> result;
    gli::texture_cube cube = gli::texture_cube(texture);
    result.resize(texture.faces());
    for (int i = 0; i < texture.faces(); i++) {
      gli::texture2d tex = cube[i];
      result[i] = std::move(readDDS(tex));
    }
    return result;
  }

  std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> ImageIO::readDDS(const gli::texture2d& texture2d){
    gli::image image = texture2d[0];

    unsigned long width = image.extent()[0];
    unsigned long height = image.extent()[1];
    std::unique_ptr<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>> result = std::make_unique<Iyathuum::MultiDimensionalArray<Iyathuum::Color, 2>>(width, height);


    std::vector<unsigned long> img;
    img.resize(width * height);

    gli::fsampler2D sampler(texture2d, gli::wrap::WRAP_REPEAT, gli::filter::FILTER_NEAREST, gli::filter::FILTER_NEAREST);

    for (size_t x = 0; x < width; x++)
      for (size_t y = 0; y < height; y++)
      {
        auto value = sampler.texel_fetch(glm::ivec2(x, y), 0);
        result->getRef({ x,y }) = Iyathuum::Color(value[0] * 255, value[1] * 255, value[2] * 255, value[3] * 255);
      }

    return result;
  }


}