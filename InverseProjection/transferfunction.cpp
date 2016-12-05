#pragma once

#include "transferfunction.h"

#include <fstream>

#include <Windows.h>

namespace vr {
  TransferControlPoint::TransferControlPoint(double r, double g, double b, int isovalue)
  {
    m_color.x = r;
    m_color.y = g;
    m_color.z = b;
    m_color.w = 1.0f;
    m_isoValue = isovalue;
  }

  TransferControlPoint::TransferControlPoint(double alpha, int isovalue)
  {
    m_color.x = 0.0f;
    m_color.y = 0.0f;
    m_color.z = 0.0f;
    m_color.w = alpha;
    m_isoValue = isovalue;
  }

  TransferFunction1D::TransferFunction1D(double v0, double v1)
    : m_v0(v0), m_v1(v1), m_built(false)
  {
    m_cpt_rgb.clear();
    m_cpt_alpha.clear();
    m_transferfunction = NULL;
  }

  TransferFunction1D::~TransferFunction1D()
  {
    m_cpt_rgb.clear();
    m_cpt_alpha.clear();
    if (m_transferfunction)
      m_transferfunction;
  }

  const char* TransferFunction1D::GetNameClass()
  {
    return "TrasnferFunction1D";
  }

  void TransferFunction1D::AddRGBControlPoint(TransferControlPoint rgb)
  {
    m_cpt_rgb.push_back(rgb);
  }

  void TransferFunction1D::AddAlphaControlPoint(TransferControlPoint alpha)
  {
    m_cpt_alpha.push_back(alpha);
  }

  void TransferFunction1D::ClearControlPoints()
  {
    m_cpt_rgb.clear();
    m_cpt_alpha.clear();
  }

  glm::vec4 TransferFunction1D::Get(double value)
  {
    if (!m_built)
      Build();

    glm::vec4 vf = glm::vec4(0);
    if (!(value >= 0.0 && value <= 255.0))
      return glm::vec4(0);

    if (value == (float)(m_tflenght - 1))
    {
      return m_transferfunction[m_tflenght - 1];
    }
    else
    {
      glm::vec4 v1 = m_transferfunction[(int)value];
      glm::vec4 v2 = m_transferfunction[((int)value) + 1];

      double t = value - (int)value;

      vf = v1*(float)(1.0 - t) + v2*(float)(t);
    }

    return vf;
  }

  void TransferFunction1D::PrintControlPoints()
  {
    printf("Print Transfer Function: Control Points\n");
    int rgb_pts = (int)m_cpt_rgb.size();
    printf("- Printing the RGB Control Points\n");
    printf("  Format: \"Number: Red Green Blue, Isovalue\"\n");
    for (int i = 0; i < rgb_pts; i++)
    {
      printf("  %d: %.2f %.2f %.2f, %d\n", i + 1, m_cpt_rgb[i].m_color.x, m_cpt_rgb[i].m_color.y, m_cpt_rgb[i].m_color.z, m_cpt_rgb[i].m_isoValue);
    }
    printf("\n");

    int alpha_pts = (int)m_cpt_alpha.size();
    printf("- Printing the Alpha Control Points\n");
    printf("  Format: \"Number: Alpha, Isovalue\"\n");
    for (int i = 0; i < alpha_pts; i++)
    {
      printf("  %d: %.2f, %d\n", i + 1, m_cpt_alpha[i].m_color.w, m_cpt_alpha[i].m_isoValue);
    }
    printf("\n");
  }

  void TransferFunction1D::PrintTransferFunction()
  {
    printf("Print Transfer Function: Control Points\n");
    printf("  Format: \"IsoValue: Red Green Blue, Alpha\"\n");
    for (int i = 0; i < m_tflenght; i++)
    {
      printf("%d: %.2f %.2f %.2f, %.2f\n", i, m_transferfunction[i].x
        , m_transferfunction[i].y, m_transferfunction[i].z, m_transferfunction[i].w);
    }
  }

  void TransferFunction1D::Build()
  {
    if (m_transferfunction)
      delete[] m_transferfunction;
    m_transferfunction = new glm::vec4[256];

    int numTF = 0;
    for (int i = 0; i < (int)m_cpt_rgb.size() - 1; i++)
    {
      int steps = m_cpt_rgb[i + 1].m_isoValue - m_cpt_rgb[i].m_isoValue;
      for (int j = 0; j < steps; j++)
      {
        float k = (float)j / (float)(steps);
        glm::vec4 diff = m_cpt_rgb[i + 1].m_color - m_cpt_rgb[i].m_color;
        diff = diff * k;
        m_transferfunction[numTF++] = m_cpt_rgb[i].m_color + diff;
      }
    }
    m_tflenght = numTF;

    numTF = 0;
    for (int i = 0; i < (int)m_cpt_alpha.size() - 1; i++)
    {
      int steps = m_cpt_alpha[i + 1].m_isoValue - m_cpt_alpha[i].m_isoValue;
      for (int j = 0; j < steps; j++)
      {
        float k = (float)j / (float)(steps);
        glm::vec4 diff = m_cpt_alpha[i + 1].m_color - m_cpt_alpha[i].m_color;
        diff = diff * k;
        m_transferfunction[numTF++].w = m_cpt_alpha[i].m_color.w + diff.w;
      }
    }

    printf("lqc: Transfer Function 1D Built!\n");
    m_built = true;
  }
}
