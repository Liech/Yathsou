#pragma once

#include <IyathuumCoreLib/lib/glm/glm.hpp>

namespace Iyathuum
{

  template <size_t Dimension>
  struct PolygonNetPolygon
  {
    using vec = glm::vec<Dimension, float, glm::defaultp>;
    std::vector<size_t>                 points;
    std::vector<PolygonNetPolygon<Dimension>*> neighbours;
  };

  template <size_t Dimension>
  struct PolygonNet
  {
    using vec = glm::vec<Dimension, float, glm::defaultp>;
    std::vector<vec                         > points;
    std::vector<PolygonNetPolygon<Dimension>> faces ;




    static PolygonNet<3> cube()
    {
      PolygonNet<3> cube;

      glm::vec3 MMM(0, 0, 0);
      glm::vec3 MMP(0, 0, 1);
      glm::vec3 MPM(0, 1, 0);
      glm::vec3 MPP(0, 1, 1);
      glm::vec3 PMM(1, 0, 0);
      glm::vec3 PMP(1, 0, 1);
      glm::vec3 PPM(1, 1, 0);
      glm::vec3 PPP(1, 1, 1);

      size_t nMMM = 0;
      size_t nMMP = 1;
      size_t nMPM = 2;
      size_t nMPP = 3;
      size_t nPMM = 4;
      size_t nPMP = 5;
      size_t nPPM = 6;
      size_t nPPP = 7;

      cube.points.push_back(MMM);
      cube.points.push_back(MMP);
      cube.points.push_back(MPM);
      cube.points.push_back(MPP);
      cube.points.push_back(PMM);
      cube.points.push_back(PMP);
      cube.points.push_back(PPM);
      cube.points.push_back(PPP);

      cube.faces.push_back(PolygonNetPolygon<3>());
      cube.faces.push_back(PolygonNetPolygon<3>());
      cube.faces.push_back(PolygonNetPolygon<3>());
      cube.faces.push_back(PolygonNetPolygon<3>());
      cube.faces.push_back(PolygonNetPolygon<3>());
      cube.faces.push_back(PolygonNetPolygon<3>());

      PolygonNetPolygon<3>* MOO = &cube.faces[0];
      PolygonNetPolygon<3>* POO = &cube.faces[1];
      PolygonNetPolygon<3>* OMO = &cube.faces[2];
      PolygonNetPolygon<3>* OPO = &cube.faces[3];
      PolygonNetPolygon<3>* OOM = &cube.faces[4];
      PolygonNetPolygon<3>* OOP = &cube.faces[5];

      OMO->points     = std::vector<size_t>               { nMMM,nMMP,nPMP,nPMM };
      OMO->neighbours = std::vector<PolygonNetPolygon<3>*>{ MOO ,OOP ,POO ,OOM  };
      OPO->points     = std::vector<size_t>               { nMPM,nPPM,nPPP,nMPP };
      OPO->neighbours = std::vector<PolygonNetPolygon<3>*>{ OOM ,POO ,OOP ,MOO  };
      MOO->points     = std::vector<size_t>               { nMMM,nMPM,nMPP,nMMP };
      MOO->neighbours = std::vector<PolygonNetPolygon<3>*>{ OOM ,OPO ,OOP ,OMO  };
      POO->points     = std::vector<size_t>               { nPMM,nPMP,nPPP,nPPM };
      POO->neighbours = std::vector<PolygonNetPolygon<3>*>{ OMO ,OOP ,OPO ,OOM  };
      OOM->points     = std::vector<size_t>               { nMMM,nPMM,nPPM,nMPM };
      OOM->neighbours = std::vector<PolygonNetPolygon<3>*>{ OMO ,POO ,OPO ,MOO  };
      OOP->points     = std::vector<size_t>               { nMMP,nMPP,nPPP,nPMP };
      OOP->neighbours = std::vector<PolygonNetPolygon<3>*>{ MOO ,OPO ,POO ,OMO  };
      return cube;
    }
  };
}