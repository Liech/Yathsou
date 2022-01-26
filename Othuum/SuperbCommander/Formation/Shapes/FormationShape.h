#pragma once

#include "IyathuumCoreLib/lib/glm/glm.hpp"
#include "IyathuumCoreLib/BaseTypes/glmAABB.h"

namespace Ahwassa {
  class BasicRectangleRenderer;
}

namespace Superb {
  namespace Formation {
    enum class FormationShapeGradientType {
      Directed,
      Spherical
    };

    class FormationShape {
    public:
      const Iyathuum::glmAABB<2>& getPosition() const;
      void                        setPosition(const Iyathuum::glmAABB<2>&);
      float                       getRotation() const;
      void                        setRotation(float degree);
      int                         getGroup() const;
      void                        setGroup(int group);

      FormationShapeGradientType  getGradientType() const;
      void                        setGradientType(FormationShapeGradientType);
      void                        setGradientDirection(const float&);
      float                       getGradientDirection() const;
      void                        setGradientCenter(const glm::vec2&);
      glm::vec2                   getGradientCenter() const;
      

      virtual void                draw(Ahwassa::BasicRectangleRenderer& renderer);

      static std::string          ShapeGradientType2String(FormationShapeGradientType);

    private:
      Iyathuum::glmAABB<2> _position;
      float                _rotation = 0;    
      int                  _group    = 0;

      FormationShapeGradientType _gradientType            = FormationShapeGradientType::Directed;
      float                      _gradientDirection       = 0.0f;
      glm::vec2                  _gradientSphericalCenter = glm::vec2(0,0);
    };
  }
}