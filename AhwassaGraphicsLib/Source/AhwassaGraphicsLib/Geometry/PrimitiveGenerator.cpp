#include "PrimitiveGenerator.h"

#include <glm/gtc/constants.hpp>


namespace Ahwassa {

  std::pair<std::vector<PositionNormalVertex>, std::vector<int>> PrimitiveGenerator::getCube() {
    std::vector<PositionNormalVertex> input;
    float start = 0;
    float end = 1;
    //front
    input.push_back(PositionNormalVertex(glm::vec3(start, start, end), glm::vec3(0, 0, 1)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, end), glm::vec3(0, 0, 1)));
    input.push_back(PositionNormalVertex(glm::vec3(end, end, end), glm::vec3(0, 0, 1)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, end), glm::vec3(0, 0, 1)));

    //right
    input.push_back(PositionNormalVertex(glm::vec3(end, end, end), glm::vec3(1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, end, start), glm::vec3(1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, start), glm::vec3(1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, end), glm::vec3(1, 0, 0)));

    //back
    input.push_back(PositionNormalVertex(glm::vec3(start, start, start), glm::vec3(0, 0, -1)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, start), glm::vec3(0, 0, -1)));
    input.push_back(PositionNormalVertex(glm::vec3(end, end, start), glm::vec3(0, 0, -1)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, start), glm::vec3(0, 0, -1)));

    //left
    input.push_back(PositionNormalVertex(glm::vec3(start, start, start), glm::vec3(-1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, start, end), glm::vec3(-1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, end), glm::vec3(-1, 0, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, start), glm::vec3(-1, 0, 0)));

    //upper
    input.push_back(PositionNormalVertex(glm::vec3(end, end, end), glm::vec3(0, 1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, end), glm::vec3(0, 1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, end, start), glm::vec3(0, 1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, end, start), glm::vec3(0, 1, 0)));

    //bottom
    input.push_back(PositionNormalVertex(glm::vec3(start, start, start), glm::vec3(0, -1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, start), glm::vec3(0, -1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(end, start, end), glm::vec3(0, -1, 0)));
    input.push_back(PositionNormalVertex(glm::vec3(start, start, end), glm::vec3(0, -1, 0)));

    //note every face of the cube is on a single line
    auto indices = std::vector<int>{
      0,  1,  2,  0,  2,  3,   //front
      4,  5,  6,  4,  6,  7,   //right
      8,  9,  10, 8,  10, 11,  //back
      12, 13, 14, 12, 14, 15,  //left
      16, 17, 18, 16, 18, 19,  //upper
      20, 21, 22, 20, 22, 23 }; //bottom
    return std::make_pair(input, indices);
  }

  std::pair<std::vector<PositionNormalVertex>, std::vector<int>> PrimitiveGenerator::getSphere() {
    //https://stackoverflow.com/questions/7687148/drawing-sphere-in-opengl-without-using-glusphere
    std::vector<PositionNormalVertex> vertecies;
    int uResolution = 15;
    int vResolution = 15;
    float r = 1;
    auto F = [](float u, float v, float r) {return glm::vec3(cos(u) * sin(v) * r, cos(v) * r, sin(u) * sin(v) * r); };
    auto triangle = [](glm::vec3 a, glm::vec3 b, glm::vec3 c) {};
    float startU = 0;
    float startV = 0;
    float endU = glm::pi<float>() * 2;
    float endV = glm::pi<float>();
    float stepU = (endU - startU) / uResolution; // step size between U-points on the grid
    float stepV = (endV - startV) / vResolution; // step size between V-points on the grid
    for (int i = 0; i < uResolution; i++) { // U-points
      for (int j = 0; j < vResolution; j++) { // V-points
        float u = i * stepU + startU;
        float v = j * stepV + startV;
        float un = (i + 1 == uResolution) ? endU : (i + 1) * stepU + startU;
        float vn = (j + 1 == vResolution) ? endV : (j + 1) * stepV + startV;
        // Find the four points of the grid
        // square by evaluating the parametric
        // surface function
        glm::vec3 p0 = F(u, v, r);
        glm::vec3 p1 = F(u, vn, r);
        glm::vec3 p2 = F(un, v, r);
        glm::vec3 p3 = F(un, vn, r);
        // NOTE: For spheres, the normal is just the normalized
        // version of each vertex point; this generally won't be the case for
        // other parametric surfaces.
        // Output the first triangle of this grid square
        glm::vec3 offset(0, 0, 0);
        vertecies.push_back(PositionNormalVertex(p0 + offset, -glm::cross(p0 - p2, p1)));
        vertecies.push_back(PositionNormalVertex(p2 + offset, -glm::cross(p0 - p2, p1)));
        vertecies.push_back(PositionNormalVertex(p1 + offset, -glm::cross(p0 - p2, p1)));
        vertecies.push_back(PositionNormalVertex(p3 + offset, glm::cross(p3 - p1, p2)));
        vertecies.push_back(PositionNormalVertex(p1 + offset, glm::cross(p3 - p1, p2)));
        vertecies.push_back(PositionNormalVertex(p2 + offset, glm::cross(p3 - p1, p2)));
      }
    }
    std::vector<int> indices;
    indices.resize(vertecies.size());
    for (size_t i = 0; i < vertecies.size(); i++)
      indices[i] = i;

    std::pair<std::vector<PositionNormalVertex>, std::vector<int>> result;
    result.first  = vertecies;
    result.second = indices;
    return result;
  }
}