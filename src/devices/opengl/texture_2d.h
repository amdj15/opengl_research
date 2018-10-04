#pragma once
#include "../../graphic/api/texture.h"

namespace Devices {
  namespace OpenGL {
    class Texture2D : public Graphic::Texture {
      private:
        int m_BPP;
        unsigned char *m_Buffer;
        unsigned int m_RendererId;

      public:
        Texture2D(const std::string &pathToFile);
        ~Texture2D();

        void Bind(unsigned int slot) const override;
        void Unbind() const override;

        inline unsigned int GetRendererId() const override { return m_RendererId; }
    };
  }
}