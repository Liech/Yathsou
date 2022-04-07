#include "STLWriter.h"

#include <fstream>

namespace Aezesel {
  void STLWriter::write(const std::string& filename, const std::vector<glm::vec3>& data) {
    std::ofstream file;
    file.open(filename);

    std::string start = "solid https://github.com/Liech/Yathsou\n";
    file.write(start.c_str(),start.size());

    std::string outerLoop = "    outer loop\n";
    std::string endloop = "    endloop\n";
    std::string endfacet = "endfacet\n";

    for (size_t i = 0; i < data.size() / 3; i++) {
      glm::vec3 a = data[i * 3 + 0];
      glm::vec3 b = data[i * 3 + 1];
      glm::vec3 c = data[i * 3 + 2];
      glm::vec3 n = glm::cross(a - b, a - c);

      std::string normals = "facet normal " + std::to_string(n[0]) + " " + std::to_string(n[1]) + " " + std::to_string(n[2]) + "\n";

      std::string v1 = "        vertex " + std::to_string(a[0]) + " " + std::to_string(a[1]) + " " + std::to_string(a[2]) + "\n";
      std::string v2 = "        vertex " + std::to_string(b[0]) + " " + std::to_string(b[1]) + " " + std::to_string(b[2]) + "\n";
      std::string v3 = "        vertex " + std::to_string(c[0]) + " " + std::to_string(c[1]) + " " + std::to_string(c[2]) + "\n";

      file.write(normals.c_str(),normals.size());
      file.write(outerLoop.c_str(),outerLoop.size());
      file.write(v1.c_str(),v1.size());
      file.write(v2.c_str(),v2.size());
      file.write(v3.c_str(),v3.size());
      file.write(endloop.c_str(),endloop.size());
      file.write(endfacet.c_str(),endfacet.size());
    }

    std::string end = "endsolid https://github.com/Liech/Yathsou\n";
    file.write(end.c_str(),end.size());
    file.close();
  }

}