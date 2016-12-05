#pragma once

#include <vector>
#include <iostream>
#include <stdio.h>

#include "glm/glm.hpp"

namespace vr
{
  class TransferControlPoint
  {
  public:
    TransferControlPoint(double r, double g, double b, int isovalue);
    TransferControlPoint(double alpha, int isovalue);

    glm::vec3 operator -(const TransferControlPoint& v)
    {
      glm::vec4 ret;
      ret = this->m_color - v.m_color;

      return glm::vec3(ret.x, ret.y, ret.z);
    }

    glm::vec3 operator +(const TransferControlPoint& v)
    {
      glm::vec4 ret;
      ret = this->m_color + v.m_color;

      return glm::vec3(ret.x, ret.y, ret.z);
    }

    glm::vec3 operator +(const glm::vec3& v)
    {
      return glm::vec3(this->m_color.x + v.x, this->m_color.y + v.y, this->m_color.z + v.z);
    }

    glm::vec4 m_color;
    int m_isoValue;
  };

  class TransferFunction
  {
  public:
    TransferFunction() {}
    ~TransferFunction() {}

    virtual const char* GetNameClass() = 0;
    virtual glm::vec4 Get(double value) = 0;

    std::string GetName() { return m_name; }
    void SetName(std::string name) { m_name = name; }

  protected:
    std::string m_name;
  private:
  };

  class TransferFunction1D : public TransferFunction
  {
  public:
    TransferFunction1D(double v0 = 0.0, double v1 = 256.0);
    ~TransferFunction1D();

    virtual const char* GetNameClass();

    void AddRGBControlPoint(TransferControlPoint rgb);
    void AddAlphaControlPoint(TransferControlPoint alpha);
    void ClearControlPoints();
    
    virtual glm::vec4 Get(double value);

    void PrintControlPoints();
    void PrintTransferFunction();
    
    void Build();
    
  private:
    bool m_built;
    std::vector<TransferControlPoint> m_cpt_rgb;
    std::vector<TransferControlPoint> m_cpt_alpha;
    glm::vec4* m_transferfunction;
    int m_tflenght;

    double m_v0, m_v1;
  };
}
