#pragma once
#include <string>

namespace Graphic {
  class Texture {
    protected:
      int m_Width, m_Height;

    public:
      Texture();
      virtual ~Texture() = default;

      virtual void Bind(unsigned int slot) const = 0;
      virtual void Unbind() const = 0;
      virtual inline unsigned int GetRendererId() const = 0;

      inline int GetWidth() const { return m_Width; }
      inline int GetHeight() const { return m_Height; }

      static Texture* Create2DFromFile(const std::string &pathToFile);
  };
}