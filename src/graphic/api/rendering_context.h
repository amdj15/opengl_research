#pragma once

namespace Graphic {
  enum class RenderingAPI { OpenGL };

  class Context {
    private:
      static Context m_Context;

    public:
      static void Create(RenderingAPI api);
  };
}
