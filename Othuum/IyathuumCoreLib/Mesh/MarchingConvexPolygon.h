#pragma once

#include "IyathuumCoreLib/BaseTypes/Line.h"

namespace Iyathuum
{

  /*
  Marching Squares in a bit more general fashion
  Assumes input polygon is convex, will spit out garbage if not
  input should be counterclockwise
  */
  template <size_t Dimension>
  class MarchingConvexPolygon
  {
    using vec = glm::vec<Dimension, float, glm::defaultp>;
  public:
    struct Result
    {
      struct LineIndexDescription
      {
        LineIndexDescription(size_t startA, size_t endA, size_t startB, size_t endB)
        {
          //make it comparable
          if (startA < endA)
            start = std::make_pair(startA, endA);
          else
            start = std::make_pair(endA, startA);
          if (startB < endB)
            start = std::make_pair(startB, endB);
          else
            start = std::make_pair(endB, startB);
        }
        std::pair<size_t, size_t> start;
        std::pair<size_t, size_t> end;
      };

      std::vector<Line<Dimension>>      lines;
      std::vector<LineIndexDescription> indices;
    };

    static std::vector<Line<2>> marchingSquares(float mm, float mp, float pm, float pp, float isovalue)
    {
      return MarchingConvexPolygon<2>({ glm::vec2(0,0), glm::vec2(1,0), glm::vec2(1,1), glm::vec2(0,1)}, { mm,pm,pp,mp }, isovalue).lines;
    }

    static Result calculate(std::vector<vec> points, std::vector<float> weights, float isovalue)
    {
      Result result;
      assert(points.size() == weights.size());
      assert(points.size() > 2);

      auto increase = [&points](size_t i) { return (i + 1) % points.size(); };

      size_t currentPosition = 0;
      vec    pointPrevious   = points.back();
      float  weightPrevious  = weights.back();
      size_t previousPosition = points.size() - 1;
      bool   streak          = false;
      size_t streakStart     = 0;      
      size_t misses          = 0;

      std::vector<Line<Dimension>>              streaks;
      std::vector<Result::LineIndexDescription> indices;

      while (currentPosition < points.size())
      {
        const float currentWeight = weights[currentPosition];
        const vec   currentPoint  = points [currentPosition];
        bool hit = currentWeight < isovalue;
        if (!hit)
          misses++;

        if (currentWeight < isovalue && streak)
        {
          //streak ends 
          Line<Dimension> currentStreak;          
          currentStreak.end   = interpolate(isovalue, points[streakStart], weights[streakStart], points[increase(streakStart)], weights[increase(streakStart)]);
          currentStreak.start = interpolate(isovalue, currentPoint,currentWeight, pointPrevious, weightPrevious);
          Result::LineIndexDescription currentI(currentPosition, previousPosition, streakStart , increase(streakStart));

          streaks.push_back(currentStreak);
          indices.push_back(currentI);
          streak = false;
        }
        else if (currentWeight > isovalue && !streak)
        {
          //streak starts
          streakStart = currentPosition;
          streak = true;
        }
        previousPosition = currentPosition;
        currentPosition++;
        weightPrevious = currentWeight;
        pointPrevious  = currentPoint;
      }

      if (misses == 0)
        return result;
      
      if (streaks.size() <= 2)
      {
        result.lines   = streaks;
        result.indices = indices;
        return result;
      }

      bool firstHit = weights[0] > isovalue;
      if (streak && firstHit){
        vec   a = points [streakStart];
        float aw = weights[streakStart];
        vec   b = points [increase(streakStart)];
        float bw = weights[increase(streakStart)];       
        streaks[0].end = interpolate(isovalue, a, aw, b, bw);
        indices[0]     = Result::LineIndexDescription(indices[0].start.first, indices[0].start.second, streakStart, increase(streakStart));
      }

      result.lines   = streaks;
      result.indices = indices;
      return result;
    }
  private:
    static vec interpolate(const float& iso, const vec& A, float a, const vec& B, float b)
    {
      return interpolate((iso - a) / (b - a), A, B);
    }

    static vec interpolate(const float& iso, const vec& A, const vec& B)
    {
      return A * iso + B * (1 - iso);
    }
  };
}