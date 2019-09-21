#pragma once

#include <cassert>
#include <string>
#include "glm/glm.hpp"
namespace YolonaOss {
  namespace GL {
    class Uniform
    {
    public:
      Uniform(std::string name) { _name = name; }
      virtual ~Uniform() {}

      std::string getName() { return _name; }
      void setLocation(int location) { assert(_location == -1); _location = location; };
      int  getLocation() { return _location; };
      bool isActive() { return _location == -1; }
      virtual void bind() = 0;
      virtual std::string toGLSL();
      virtual std::string getType() = 0;
      virtual bool isBuffer() { return false; }
    private:
      std::string _name;
      int _location = -1;
    };

    class UniformFloat : public Uniform {
    public:
      UniformFloat(std::string name) : Uniform(name) {};
      void  setValue(float val);
      float getValue();

      void bind() override;
      std::string getType() override { return "float"; }

    private:
      float _value = 0;
    };

    class UniformVec2 : public Uniform {
    public:
      UniformVec2(std::string name) : Uniform(name) {};
      void  setValue(glm::vec2 val);
      glm::vec2 getValue();

      void bind() override;
      std::string getType() override { return "vec2"; }

    private:
      glm::vec2 _value = glm::vec2(0, 0);
    };

    class UniformVec3 : public Uniform {
    public:
      UniformVec3(std::string name) : Uniform(name) {};
      void  setValue(glm::vec3 val);
      glm::vec3 getValue();

      void bind() override;
      std::string getType() override { return "vec3"; }

    private:
      glm::vec3 _value = glm::vec3(0, 0, 0);
    };
    class UniformVec4 : public Uniform {
    public:
      UniformVec4(std::string name) : Uniform(name) {};
      void  setValue(glm::vec4 val);
      glm::vec4 getValue();

      void bind() override;
      std::string getType() override { return "vec4"; }

    private:
      glm::vec4 _value = glm::vec4(0, 0, 0, 0);
    };
    class UniformMat4 : public Uniform {
    public:
      UniformMat4(std::string name) : Uniform(name) {};
      void  setValue(glm::mat4 val);
      glm::mat4 getValue();

      void bind() override;
      std::string getType() override { return "mat4"; }

    private:
      glm::mat4 _value = glm::mat4(1.0);
    };
  }
}