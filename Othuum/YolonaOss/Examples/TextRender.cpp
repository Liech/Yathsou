#include "TextRender.h"
#include <ft2build.h>
#include FT_FREETYPE_H  
#include <filesystem>
#include <iostream>


TextRender::TextRender()
{
}


TextRender::~TextRender()
{
}

void TextRender::load(DrawSpecification *d)
{
  _spec = d;
  FT_Library  library;   /* handle to library     */
  FT_Face     face;      /* handle to face object */


  int error = FT_Init_FreeType(&library);
  if (error) { throw std::runtime_error(":("); }
  std::filesystem::path cwd = std::filesystem::current_path();
  std::cout << cwd.string() << std::endl;
  
  std::string path = cwd.string() + "/" + "YolonaOssData/fonts/arial.ttf";
  error = FT_New_Face(library,
    path.c_str(),
    0,
    &face);
  if (error == FT_Err_Unknown_File_Format)
  {
   // ... the font file could be opened and read, but it appears
   //   ... that its font format is unsupported
    throw std::runtime_error(":(");
  }
  else if (error)
  {
   // ... another error code means that the font file could not
   //   ... be opened or read, or that it is broken...
    throw std::runtime_error(":(");
  }
}

void TextRender::draw()
{

}
